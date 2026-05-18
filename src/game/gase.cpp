/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gase.hpp"


// Default world parameters
Gase Gase::environment{1.0, 20.0};

Gase::Gase() {}

Gase::Gase(float _pressure, float _temperature) {
    temperature = _temperature;
    mass = _pressure * volume / _temperature;
}

void Gase::reset() {
    // Setting parameters to global
    temperature = environment.temperature;
    mass = environment.mass;
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

float Gase::getMassFlow(const Gase& _second, float _power) const {
    float d = mass*temperature - _second.mass*_second.temperature + _power;
    /*if (d > 0) {
        return SDL_sqrtf(d) * pressureKoef;
    } else {
        return -SDL_sqrtf(-d) * pressureKoef;
    }*/
    return d * pressureKoef;
}

void Gase::exchange(Gase& _dest) const {
    // Getting change
    float deltaMass = getMassFlow(environment);

    // Changing temperture (not affecting enviroment)
    if (deltaMass > 0.0) {
        _dest.temperature = (_dest.mass*_dest.temperature-deltaMass*environment.temperature) / (_dest.mass-deltaMass);
    }
    // Changing mass
    _dest.mass -= deltaMass;
}

void Gase::exchange(const Gase& _src2, Gase& _dst1, Gase& _dst2) const {
    // Getting change
    float deltaMass = getMassFlow(_src2);

    // Changing temperture
    if (deltaMass > 0.0) {
        _dst2.temperature = (_dst2.mass*_dst2.temperature+deltaMass*temperature) / (_dst2.mass+deltaMass);
    } else {
        _dst1.temperature = (_dst1.mass*_dst1.temperature-deltaMass*_src2.temperature) / (_dst1.mass-deltaMass);
    }
    // Changing mass
    _dst1.mass -= deltaMass;
    _dst2.mass += deltaMass;
}

void Gase::vent(const Gase& _srcOut, Gase& _dstIn, Gase& _dstOut, float _power) const {
    // Getting change
    float deltaMass = getMassFlow(_srcOut, _power);

    // Changing temperture
    if (deltaMass > 0.0) {
        _dstOut.temperature = (_dstOut.mass*_dstOut.temperature+deltaMass*temperature) / (_dstOut.mass+deltaMass);
    } else {
        _dstIn.temperature = (_dstIn.mass*_dstIn.temperature-deltaMass*_srcOut.temperature) / (_dstIn.mass-deltaMass);
    }
    // Changing mass
    _dstIn.mass -= deltaMass;
    _dstOut.mass += deltaMass;
}

void Gase::exchangeValved(const Gase& _srcOut, Gase& _dstIn, Gase& _dstOut) const {
    // Getting change
    float deltaMass = getMassFlow(_srcOut);

    // Allow only to one side
    if (deltaMass > 0) {
        // Changing temperature
        _dstOut.temperature = (_dstOut.mass*_dstOut.temperature+deltaMass*temperature) / (_dstOut.mass+deltaMass);
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
