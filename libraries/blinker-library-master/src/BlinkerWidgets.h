#ifndef BlinkerWidgets_H
#define BlinkerWidgets_H

#include <utility/BlinkerButton.h>
#include <utility/BlinkerJoystick.h>
#include <utility/BlinkerNumber.h>
#include <utility/BlinkerRGB.h>
#include <utility/BlinkerSlider.h>
#include <utility/BlinkerSwitch.h>
#include <utility/BlinkerText.h>

#if defined(BLINKER_ALIGENIE)
    #include <utility/BlinkerAliGenie.h>

    BLINKERALIGENIE BlinkerAliGenie;
#endif

BlinkerSwitch BUILTIN_SWITCH;

#endif
