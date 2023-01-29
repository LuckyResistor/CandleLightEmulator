// Copyright (C) 2023 Lucky Resistor.
// Web: https://luckyresistor.me
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "Application.hpp"


#include "Configuration.hpp"
#include "RandomWave.hpp"
#include "RandomSuppressor.hpp"
#include "Display.hpp"
#include "Tools.hpp"


namespace lr::Application {


/// A slow random wave, emulating variations in the burn rate.
///
RandomWave gSlowWave{{100, 180, 3000, 6000}};

/// A fast random wave, emulating flickering in a draft.
///
RandomWave gFastWave{{-40, 40, 20, 120}};

/// A steady random wave, emulating directional movements of the flame.
///
RandomWave gTiltWave{{-1000, 1000, 400, 800}};

/// A peak suppressor, emulating random drafts passing the candle.
///
RandomSuppressor gSuppressor{{3000, 10000}};


void setup() noexcept {
    Display::initialize();
    randomSeed(analogRead(0));
    auto currentTime = millis();
    gFastWave.initialize(currentTime);
    gTiltWave.initialize(currentTime);
    gSlowWave.initialize(currentTime);
    gSuppressor.initialize(currentTime);
}


/// Test the display levels.
///
/// Replace `emulateCandle()` in the `loop()` method with this one, to test and
/// calibrate the light colours and levels.
///
void ledTest() noexcept {
    static uint32_t count = 0;
    if (count & 0x100) {
        Display::setLevel(count & 0xff);
    } else {
        Display::setLevel(0xff - (count & 0xff));
    }
    ++count;
    delay(10);
}


/// Emulate candle light.
///
void emulateCandle() noexcept {
    auto currentTime = millis();
    auto level = gSlowWave.valueAt(currentTime);
    auto suppression = gSuppressor.valueAt(currentTime);
    level += (gFastWave.valueAt(currentTime) * suppression) / int16_t{1000};
    auto tilt = gTiltWave.valueAt(currentTime);
    auto displayLevel = static_cast<Display::Level>(clamp(level, int16_t{0}, int16_t{255}));
    Display::setLevel(displayLevel, tilt);
    delay(5);
}


void loop() noexcept {
    emulateCandle();
}


}

