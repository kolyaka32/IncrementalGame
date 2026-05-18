/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gase.hpp"


// Default world parameters
float Gase::globalPressure = 1.0;
float Gase::globalTemperature = 20.0;

Gase::Gase() {}

void Gase::reset() {
    // Setting parameters to global
    temperature = globalTemperature;
    mass = globalPressure * volume / temperature;
}

void Gase::addMass(float _change) {
    // Temperature doesn't change
    mass *= _change;
}

void Gase::reduceMass(float _change) {
    // Temperature doesn't change
    mass /= _change;
}

void Gase::addTemperature(float _power) {
    // Mass stay constant
    temperature += _power * heatCapacity;
}

float Gase::getPressure() const {
    return mass * temperature / volume;
}

float Gase::getMass() const {
    return mass;
}

float Gase::getTemperature() const {
    return temperature;
}

void Gase::exchange(Gase& _dest) const {
    // Calculating mass flow (signed)
    float pressure = getPressure();

    // Check direction
    if (globalPressure > pressure) {
        float deltaMass = (globalPressure - pressure) * pressureKoef;
        // Changing temperture
        _dest.temperature = (mass*temperature-deltaMass*globalTemperature) / (mass-deltaMass);
        // Changing mass
        _dest.mass += deltaMass;
    } else {
        float deltaMass = (pressure - globalPressure) * pressureKoef;
        // Changing mass
        _dest.mass += deltaMass;
    }
}

void Gase::exchange(const Gase& _src2, Gase& _dst1, Gase& _dst2) const {
    // Calculating mass flow (signed)
    float pressure = getPressure();
    float pressure2 = _src2.getPressure();

    // Changing temperture
    if (pressure > pressure2) {
        float deltaMass = (pressure - pressure2) * pressureKoef;
        // Changing temperature
        _dst2.temperature = (_src2.mass*_src2.temperature+deltaMass*temperature) / (_src2.mass+deltaMass);
        // Changing mass
        _dst1.mass -= deltaMass;
        _dst2.mass += deltaMass;
    } else {
        float deltaMass = (pressure2 - pressure) * pressureKoef;
        // Changing temperature
        _dst1.temperature = (mass*temperature-deltaMass*_src2.temperature) / (mass-deltaMass);
        // Changing mass
        _dst1.mass += deltaMass;
        _dst2.mass -= deltaMass;
    }
}

void Gase::vent(const Gase& _srcOut, Gase& _dstIn, Gase& _dstOut, float _power) const {
    // Calculating mass flow (signed)
    float pressure = getPressure();
    float pressure2 = _srcOut.getPressure();

    // Changing temperture
    if (pressure > pressure2) {
        float deltaMass = (pressure - pressure2 + _power) * pressureKoef;
        // Changing temperature
        _dstOut.temperature = (_srcOut.mass*_srcOut.temperature+deltaMass*temperature) / (_srcOut.mass+deltaMass);
        // Changing mass
        _dstIn.mass -= deltaMass;
        _dstOut.mass += deltaMass;
    } else {
        float deltaMass = (pressure2 - pressure - _power) * pressureKoef;
        // Changing temperature
        _dstIn.temperature = (mass*temperature-deltaMass*_srcOut.temperature) / (mass-deltaMass);
        // Changing mass
        _dstIn.mass += deltaMass;
        _dstOut.mass -= deltaMass;
    }
}

void Gase::exchangeValved(const Gase& _srcOut, Gase& _dstIn, Gase& _dstOut) const {
    // Calculating mass flow (signed)
    float pressure = getPressure();
    float pressure2 = _srcOut.getPressure();

    // Allow only to one side
    if (pressure > pressure2) {
        float deltaMass = (pressure - pressure2) * pressureKoef;
        // Changing temperature
        _dstOut.temperature = (_srcOut.mass*_srcOut.temperature+deltaMass*temperature) / (_srcOut.mass+deltaMass);
        // Changing mass
        _dstIn.mass -= deltaMass;
        _dstOut.mass += deltaMass;
    }
}

void Gase::blitThermal(const Window& _window, SDL_FRect _rect) const {
    if (temperature < 0) {
        _window.setDrawColor({0, 0, 0, 255});
    } else if (temperature < 255/drawTemperatureKoef) {
        _window.setDrawColor({Uint8(temperature*drawTemperatureKoef), 0, 0, 255});
    } else {
        _window.setDrawColor({255, 0, 0, 255});
    }
    _window.drawRect(_rect);
}

void Gase::blitPressure(const Window& _window, SDL_FRect _rect) const {
    float pressure = getPressure();

    // Doesn't check less then 0
    if (pressure > 255/drawPressureKoef) {
        _window.setDrawColor({0, 0, 255, 255});
    } else {
        _window.setDrawColor({0, 0, Uint8(pressure*drawPressureKoef), 255});
    }
    _window.drawRect(_rect);
}
