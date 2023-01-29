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
#pragma once


#include <Arduino.h>


namespace lr {


/// The pin where the data signal of the LED chips is attached.
constexpr auto cLedPin = 0;

/// The number of rows with LEDs (>=2)
constexpr auto cLedRows = 4;

/// The number of columns with LEDs (>=3)
constexpr auto cLedColumns = 5;

/// The resulting total LED count. (do not change)
constexpr auto cLedCount = cLedRows * cLedColumns;

/// The base brightness of the LEDs (0-100).
constexpr auto cLedBrightness = 50;

/// The offset of the color levels per row (>0)
/// For more rows, you might like a smaller offset.
constexpr auto cColorOffsetPerRow = 16;

/// The base hue for the LEDs. (16bit)
constexpr uint16_t cHueBase = 0x0400;

/// The factor increasing the hue per level.
constexpr uint16_t cHueFactor = 12;

/// A cut off for the HSV value, to prevent too much red at very dark colours.
constexpr uint8_t cValueCutOff = 28;


}

