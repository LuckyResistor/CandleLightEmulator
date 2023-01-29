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
#include "RandomWave.hpp"


namespace lr {


RandomWave::RandomWave(Config config) noexcept
    : _config{config}, _startTime{0}, _currentDuration{0}, _startValue{0}, _endValue{0} {
}


void RandomWave::initialize(TimeValue currentTime) noexcept {
    _startTime = currentTime;
    _endValue = static_cast<Value>(random(_config.minimumValue, _config.maximumValue));
    nextRandom(currentTime);
}


auto RandomWave::valueAt(TimeValue currentTime) noexcept -> Value {
    TimeValue timeDelta = currentTime - _startTime;
    if (timeDelta >= _currentDuration) {
        nextRandom(currentTime);
        timeDelta = 0;
    }
    SignedTimeValue factor = 1000;
    SignedTimeValue normal =
        (static_cast<SignedTimeValue>(timeDelta) * factor) / static_cast<SignedTimeValue>(_currentDuration);
    SignedTimeValue a = static_cast<SignedTimeValue>(_endValue) * normal;
    SignedTimeValue b = static_cast<SignedTimeValue>(_startValue) * (factor - normal);
    return static_cast<Value>((a + b) / factor);
}


void RandomWave::nextRandom(TimeValue currentTime) noexcept {
    _startValue = _endValue;
    _startTime = currentTime;
    _currentDuration = random(_config.minimumDuration, _config.maximumDuration);
    _endValue = static_cast<Value>(random(_config.minimumValue, _config.maximumValue));
}


}