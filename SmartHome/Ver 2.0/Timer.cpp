#include <Arduino.h>
#include "Timer.h"

Timer::Timer() { }

Timer::~Timer() { } 

void Timer::initialize() {
	_lastTick = millis();
}

void Timer::update() {
	_currentTick = millis();
}

unsigned long Timer::delta() {
	return _currentTick - _lastTick;
}

void Timer::resetTick() {
	_lastTick = _currentTick;
}
