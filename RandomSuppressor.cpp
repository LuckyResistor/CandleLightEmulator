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
#include "RandomSuppressor.hpp"


namespace lr {


RandomSuppressor::RandomSuppressor(RandomSuppressor::Config config) noexcept
    : _config{config}, _startTime{0}, _currentDuration{0} {
}


void RandomSuppressor::initialize(RandomSuppressor::TimeValue currentTime) noexcept {
    _startTime = currentTime;
    nextRandom(currentTime);
}


auto RandomSuppressor::valueAt(RandomSuppressor::TimeValue currentTime) noexcept -> RandomSuppressor::Value {
    TimeValue timeDelta = currentTime - _startTime;
    if (timeDelta >= _currentDuration) {
        nextRandom(currentTime);
        timeDelta = 0;
    }
    constexpr Value factor = 1000;
    SignedTimeValue normal =
        (static_cast<SignedTimeValue>(timeDelta) * factor) / static_cast<SignedTimeValue>(_currentDuration);
    if (normal >= (factor / 2)) {
        normal = factor - normal;
    }
    normal *= 2;
    normal = (normal * normal) / factor; // quad1
    normal = (normal * normal) / factor; // quad2
    return static_cast<Value>(normal);
}


void RandomSuppressor::nextRandom(RandomSuppressor::TimeValue currentTime) noexcept {
    _startTime = currentTime;
    _currentDuration = random(_config.minimumDuration, _config.maximumDuration);
}


}


