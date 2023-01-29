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


/// A class that is generating a random wave with a defined timing and value range.
///
class RandomWave {
public:
  /// The value type created for the wave.
  ///
  using Value = int16_t;

  /// The value that the `millis()` method is using.
  ///
  using TimeValue = uint32_t;

  /// A signed time value, used for the calculation.
  ///
  /// Specified due the lack of <type_traits> in the AVR toolchain.
  ///
  using SignedTimeValue = int32_t;

  /// The configuration for the random wave.
  ///
  struct Config {
    Value minimumValue;
    Value maximumValue;
    TimeValue minimumDuration;
    TimeValue maximumDuration; 
  };

public:
  /// Create a new random wave.
  ///
  /// @param config The configuration.
  ///
  explicit RandomWave(Config config) noexcept;

public:
  /// Initialize the random wave.
  ///
  /// Call this from `setup()` once.
  ///
  /// @param currentTime The current time from the `millis()` function.
  ///
  void initialize(TimeValue currentTime) noexcept;

  /// Get the current value of the wave.
  ///
  /// Call this method from the `loop()` method.
  ///
  /// @param currentTime The current time from the `millis()` function.
  ///
  auto valueAt(TimeValue currentTime) noexcept -> Value;

private:
  /// Initialize the values for a next section of the wave.
  ///
  /// @param currentTime The current time from the `millis()` function.
  ///
  void nextRandom(TimeValue currentTime) noexcept;

private:
  Config _config; ///< The configuration.
  TimeValue _startTime; ///< The start time of the current section.
  TimeValue _currentDuration; ///< The duration for the current section.
  Value _startValue; ///< The start value for the current section.
  Value _endValue; ///< The end value for the current section.
};


}

