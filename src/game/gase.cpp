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
    // Setting temporary variables to basic
    newMass = mass;
    newEnergy = mass * temperature;
}

void Gase::reset() {
    // Setting parameters to global
    temperature = environment.temperature;
    mass = environment.mass;
    // Setting temporary variables to basic
    newMass = mass;
    newEnergy = mass * temperature;
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

void Gase::addMass(float _change) {
    // Temperature doesn't change
    newMass *= _change;
    newEnergy *= _change;
}

void Gase::reduceMass(float _change) {
    // Temperature doesn't change
    newMass /= _change;
    newEnergy /= _change;
}

void Gase::addTemperature(float _power) {
    // Mass stay constant
    newEnergy += _power * heatCapacity * mass;
}

float Gase::getMassFlow(const Gase& _second, float _power) const {
    float d = (mass * temperature - _second.mass * _second.temperature + _power) / (temperature + _second.temperature);
    return d * pressureKoef;
}

void Gase::exchange() {
    // Getting change
    float deltaMass = getMassFlow(environment);

    // Changing temperture (not affecting enviroment)
    if (deltaMass > 0) {
        newEnergy -= deltaMass * environment.temperature;
    } else {
        newEnergy -= deltaMass * temperature;
    }

    // Changing mass
    newMass -= deltaMass;
}

void Gase::exchange(Gase& _other) {
    // Getting change
    float deltaMass = getMassFlow(_other);

    // Changing temperture
    if (deltaMass > 0) {
        newEnergy -= deltaMass * temperature;
        _other.newEnergy += deltaMass * temperature;
    } else {
        newEnergy -= deltaMass * _other.temperature;
        _other.newEnergy += deltaMass * _other.temperature;
    }

    // Changing mass
    newMass -= deltaMass;
    _other.newMass += deltaMass;
}

void Gase::vent(Gase& _outGase, float _power) {
    // Getting change
    float deltaMass = getMassFlow(_outGase, _power);

    // Changing temperture
    if (deltaMass > 0) {
        newEnergy -= deltaMass * temperature;
        _outGase.newEnergy += deltaMass * temperature;
    } else {
        newEnergy -= deltaMass * _outGase.temperature;
        _outGase.newEnergy += deltaMass * _outGase.temperature;
    }

    // Changing mass
    newMass -= deltaMass;
    _outGase.newMass += deltaMass;
}

void Gase::exchangeValved(Gase& _outGase) {
    // Getting change
    float deltaMass = getMassFlow(_outGase);

    // Allow only to one side
    if (deltaMass > 0) {
        // Changing temperture
        newEnergy -= deltaMass * temperature;
        _outGase.newEnergy += deltaMass * temperature;

        // Changing mass
        newMass -= deltaMass;
        _outGase.newMass += deltaMass;
    }
}

void Gase::applyChanges() {
    mass = newMass;
    temperature = newEnergy / mass;
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
