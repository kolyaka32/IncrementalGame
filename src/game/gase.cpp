/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gase.hpp"


Gase::Gase() {}

void Gase::reset() {
    pressure = 1.0;
    temperature = 20.0;
}

void Gase::applyPressure(float _pressure) {
    pressure *= SDL_pow(2, _pressure);
}

void Gase::applyTemperature(float _changeTemperature) {
    pressure *= (temperature + _changeTemperature) / temperature;
    temperature += _changeTemperature;
}

void Gase::heatUpTo(Gase& _dest, float _targetTemp) const {
    _dest.applyTemperature((_targetTemp - temperature) * temperatureKoef);
}

float Gase::getPressure() const {
    return pressure;
}

float Gase::getTemperature() const {
    return temperature;
}

void Gase::exchange(const Gase& _src2, Gase& _dst1, Gase& _dst2) const {
    // Calculating difference (signed)
    float diff = pressure - _src2.pressure;
    float velocity = diff * pressureKoef;

    // Changing temperture
    if (velocity > 0) {
        _dst2.temperature = (velocity*temperature+_src2.pressure*_src2.temperature) / (velocity+_src2.pressure);
    } else {
        _dst1.temperature = (pressure*temperature-velocity*_src2.temperature) / (pressure-velocity);
    }

    // Changing pressure
    _dst1.pressure -= velocity;
    _dst2.pressure += velocity;
}

void Gase::vent(const Gase& _srcOut, Gase& _dstIn, Gase& _dstOut, float _power) const {
    float delta = _srcOut.pressure * _power;

    // Check for not pumping to vacum
    if (delta > 0.1) {
        // Change dest pressure
        _dstOut.temperature = (_srcOut.pressure*temperature + delta*temperature) / (_srcOut.pressure+delta);

        // Change pressure
        _dstIn.pressure -= delta;
        _dstOut.pressure += delta;
    }
}

void Gase::blitThermal(const Window& _window, SDL_FRect _rect) const {
    if (temperature < 0) {
        _window.setDrawColor({0, 0, 0, 255});
    } else if (temperature < 100.0) {
        _window.setDrawColor({Uint8(temperature*2.5f), 0, 0, 255});
    } else {
        _window.setDrawColor({255, 0, 0, 255});
    }
    _window.drawRect(_rect);
}

void Gase::blitPressure(const Window& _window, SDL_FRect _rect) const {
    if (pressure > 2.54) {
        _window.setDrawColor({0, 0, 255, 255});
    } else {
        _window.setDrawColor({0, 0, Uint8(pressure*100.0f), 255});
    }
    _window.drawRect(_rect);
}
