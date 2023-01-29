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


namespace lr::Display {


/// The intensity level.
///
using Level = uint8_t;

/// The tilt level.
///
using TiltAngle = int16_t;

/// A RGB color value.
///
using Color = uint32_t;


/// Initialize the display.
///
/// Call this method once in `setup()`.
///
void initialize() noexcept;


/// Set the whole display to one intensity.
///
/// @param level The current display level from 64-192 (but can be 0-255)
///
void setLevel(Level level, TiltAngle tiltAngle = 0) noexcept;


}

