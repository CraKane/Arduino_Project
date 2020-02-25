#ifndef BlinkerSimplerESP32_H
#define BlinkerSimplerESP32_H

#include <Adapters/BlinkerArduinoWS.h>
#include <ESPmDNS.h>
#include <WiFi.h>

#if defined(BLINKER_APCONFIG)
static WiFiServer *_server;
static WiFiClient _client;
static IPAddress apIP(192, 168, 4, 1);
#endif

class BlinkerSimpleESP32_WS 
    : public BlinkerProtocol<BlinkerArduinoWS>
{
    typedef BlinkerProtocol<BlinkerArduinoWS> Base;

    public :
        BlinkerSimpleESP32_WS(BlinkerArduinoWS &transp)
            : Base(transp)
        {}

#if defined(BLINKER_ESP_SMARTCONFIG)
        void begin() {
            Base::begin();
            if (!autoInit())
                smartconfig();
            Base::loadTimer();
            BLINKER_LOG1(BLINKER_F("ESP32_WiFi initialized..."));
        }
// #endif
#elif defined(BLINKER_APCONFIG)
        void begin() {
            Base::begin();
            if (!autoInit()) {
                softAPinit();
                while(WiFi.status() != WL_CONNECTED) {
                    serverClient();

                    ::delay(10);
                }
            }
            Base::loadTimer();
            BLINKER_LOG1(BLINKER_F("ESP8266_WiFi initialized..."));
        }
#else
        void begin(const char* _ssid,
                    const char* _pswd)
        {
            Base::begin();
            connectWiFi(_ssid, _pswd);
            Base::loadTimer();
            BLINKER_LOG1(BLINKER_F("ESP32_WiFi initialized..."));
        }
#endif

    private :
#if defined(BLINKER_APCONFIG)
        void softAPinit()
        {
            _server = new WiFiServer(80);

            WiFi.mode(WIFI_AP);
            String softAP_ssid = "DiyArduino_" + macDeviceName();
            WiFi.setHostname(softAP_ssid.c_str());            
            WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
            WiFi.softAP(softAP_ssid.c_str(), "12345678");
            delay(100);

            _server->begin();
            BLINKER_LOG2(BLINKER_F("AP IP address: "), WiFi.softAPIP());
            BLINKER_LOG1(BLINKER_F("HTTP _server started"));
            BLINKER_LOG2(BLINKER_F("URL: http://"), WiFi.softAPIP());
        }

        void serverClient()
        {
            if (!_client)
            {
                _client = _server->available();
            }
            else
            {
                if (!_client.connected())
                {
                    _client.stop();
                    BLINKER_LOG1(BLINKER_F("Connection closed on _client"));
                }
                else
                {
                    if (_client.available())
                    {
                        String data = _client.readStringUntil('\r');

                        // data = data.substring(4, data.length() - 9);
                        _client.flush();

                        // BLINKER_LOG2("clientData: ", data);

                        if (STRING_contains_string(data, "ssid") && STRING_contains_string(data, "pswd")) {

                            String msg = "{\"hello\":\"world\"}";
                            
                            String s= "HTTP/1.1 200 OK\r\nContent-Type: application/json;charset=utf-8\r\n";
                            s += String("Content-Length: " + String(msg.length()) + "\r\n" +  
                                "Connection: Keep Alive\r\n\r\n" +  
                                msg + "\r\n");

                            _client.print(s);
                            
                            _client.stop();

                            parseUrl(data);
                        }
                    }
                }
            }
        }

        bool parseUrl(String data)
        {
            BLINKER_LOG2(BLINKER_F("APCONFIG data: "), data);
            DynamicJsonBuffer jsonBuffer;
            JsonObject& wifi_data = jsonBuffer.parseObject(data);
            
            if (!wifi_data.success()) {
                return false;
            }

            String _ssid = wifi_data["ssid"];
            String _pswd = wifi_data["pswd"];

            BLINKER_LOG2(BLINKER_F("ssid: "), _ssid);
            BLINKER_LOG2(BLINKER_F("pswd: "), _pswd);

            free(_server);
            connectWiFi(_ssid, _pswd);
            return true;
        }
#endif

        bool autoInit() {
            WiFi.mode(WIFI_STA);
            String _hostname = "DiyArduino_" + macDeviceName();
            WiFi.setHostname(_hostname.c_str());

            WiFi.begin();
            ::delay(500);
            BLINKER_LOG3(BLINKER_F("Waiting for WiFi "),BLINKER_WIFI_AUTO_INIT_TIMEOUT / 1000,
                BLINKER_F("s, will enter SMARTCONFIG or APCONFIG while WiFi not connect!"));
            uint8_t _times = 0;
            while (WiFi.status() != WL_CONNECTED) {
                ::delay(500);
                if (_times > BLINKER_WIFI_AUTO_INIT_TIMEOUT / 500) break;
                _times++;
            }

            if (WiFi.status() != WL_CONNECTED) return false;
            else {
                BLINKER_LOG1(BLINKER_F("WiFi Connected."));

                BLINKER_LOG1(BLINKER_F("IP Address: "));
                BLINKER_LOG1(WiFi.localIP());

                mDNSInit();
                return true;
            }
        }

#if defined(BLINKER_ESP_SMARTCONFIG)
        void smartconfig() {
            WiFi.mode(WIFI_STA);
            String _hostname = "DiyArduino_" + macDeviceName();
            WiFi.setHostname(_hostname.c_str());
            WiFi.beginSmartConfig();
            
            BLINKER_LOG1(BLINKER_F("Waiting for SmartConfig."));
            while (!WiFi.smartConfigDone()) {
                ::delay(500);
            }

            BLINKER_LOG1(BLINKER_F("SmartConfig received."));
            
            BLINKER_LOG1("Waiting for WiFi");
            while (WiFi.status() != WL_CONNECTED) {
                ::delay(500);
            }

            BLINKER_LOG1(BLINKER_F("WiFi Connected."));

            BLINKER_LOG1(BLINKER_F("IP Address: "));
            BLINKER_LOG1(WiFi.localIP());

            mDNSInit();
        }
#endif

        void mDNSInit()
        {
            if (!MDNS.begin(macDeviceName().c_str())) {
                while(1) {
                    ::delay(100);
                }
            }

            BLINKER_LOG1(BLINKER_F("mDNS responder started"));
            
            MDNS.addService("DiyArduino", "tcp", WS_SERVERPORT);
            MDNS.addServiceTxt("DiyArduino", "tcp", "deviceName", macDeviceName());

            this->conn.begin(macDeviceName());
        }

        void connectWiFi(String _ssid, String _pswd)
        {
            connectWiFi(_ssid.c_str(), _pswd.c_str());
        }

        void connectWiFi(const char* _ssid, const char* _pswd)
        {
            uint32_t connectTime = millis();

            BLINKER_LOG2(BLINKER_F("Connecting to "), _ssid);
            
            WiFi.mode(WIFI_STA);
            String _hostname = "DiyArduinoMQTT_" + macDeviceName();
            WiFi.setHostname(_hostname.c_str());

            if (_pswd && strlen(_pswd)) {
                WiFi.begin(_ssid, _pswd);
            }
            else {
                WiFi.begin(_ssid);
            }

            while (WiFi.status() != WL_CONNECTED) {
                ::delay(50);

                if (millis() - connectTime > BLINKER_CONNECT_TIMEOUT_MS && WiFi.status() != WL_CONNECTED) {
                    connectTime = millis();
                    BLINKER_LOG1(BLINKER_F("WiFi connect timeout, please check ssid and pswd!"));
                    BLINKER_LOG1(BLINKER_F("Retring WiFi connect again!"));
                }
            }
            BLINKER_LOG1(BLINKER_F("Connected"));

            IPAddress myip = WiFi.localIP();
            BLINKER_LOG2(BLINKER_F("Your IP is: "), myip);

            mDNSInit();
        }
};

static BlinkerArduinoWS  _blinkerTransport;
BlinkerSimpleESP32_WS Blinker(_blinkerTransport);

#include <BlinkerWidgets.h>

#endif
