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

#include "Display.hpp"


#include "Configuration.hpp"
#include "Tools.hpp"

#include <Adafruit_NeoPixel.h>


namespace lr::Display {


Adafruit_NeoPixel strip(cLedCount, cLedPin, NEO_GRB + NEO_KHZ800);


void initialize() noexcept {
    strip.begin();
    strip.show();
    strip.setBrightness(cLedBrightness);
}


/// Calculate the color for a given level of light intensity.
///
/// For the hue, make a transition from red to yellow.
/// For the value, go from 0 to 100%
/// for the saturation, start with 100%, then from 128, drop down to 0%.
///
/// @param level The level of the color from 0-255
/// @return The color value for this level.
///
auto colorForLevel(Level level) noexcept -> Color {
    uint16_t hue{cHueBase};
    if (level > 64) {
        hue = uint16_t{level} * cHueFactor + cHueBase;
    }
    uint8_t saturation{255};
    if (level >= uint8_t{128}) {
        saturation = uint8_t{255} - ((level - uint8_t{128}) / uint8_t{4});
    }
    uint8_t value{};
    if (level >= 192) {
        value = 255;
    } else if (level >= 64) {
        value = (level - uint8_t{64}) * uint8_t{2};
    }
    if (value < cValueCutOff) {
        return strip.Color(0, 0, 0);
    }
    return strip.ColorHSV(hue, saturation, value);
}


void setLevel(Level level, TiltAngle tiltAngle) noexcept {
    int16_t level16 = static_cast<int16_t>(level);
    for (int16_t row = 0; row < cLedRows; ++row) {
        int16_t rowLevel = level16 - cColorOffsetPerRow * row;
        for (int16_t column = 0; column < cLedColumns; ++column) {
            int16_t tiltFactor = static_cast<int16_t>((column <= cLedColumns / 2) ? column : (cLedColumns - column));
            int16_t tiltLevelDelta = (tiltFactor * tiltAngle) / (100 * (cLedColumns / 2));
            Level level = static_cast<Level>(clamp(rowLevel + tiltLevelDelta, 0, 255));
            auto color = colorForLevel(level);
            strip.setPixelColor(row * cLedColumns + column, color);
        }
    }
    strip.show();
}


}

