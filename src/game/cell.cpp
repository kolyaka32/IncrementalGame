/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cell.hpp"


Cell::Cell() {}

void Cell::reset() {
    state = Air;
    pressure = 1.0;
    temperature = 20.0;
}

bool Cell::isWall() const {
    return state & wallMask;
}

bool Cell::isVent() const {
    return state & stateMask == VentUp;
}

void Cell::applyPressure(float _pressure) {
    pressure *= SDL_pow(2, _pressure);
}

void Cell::applyTemperature(float _temperature) {
    temperature += _temperature;
}

float Cell::getPressure() const {
    return pressure;
}

float Cell::getTemperature() const {
    return temperature;
}

void Cell::exchange(const Cell& _src2, Cell& _dst1, Cell& _dst2) const {
    // Exchange only if both air
    if (!isWall() && !_src2.isWall()) {
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
}

void Cell::update() {
    switch (state) {
    case Air:
    case Wall:
        // Do nothing
        return;

    case Heater:
        // Heating up to target
        temperature += (heatTarget-temperature)*temperatureKoef;
        return;

    case VentUp:
        // !
        break;

    case VentRight:
        // !
        break;

    case VentDown:
        // !
        break;

    case VentLeft:
        // !
        break;
    
    default:
        break;
    }
}

void Cell::blitNormal(const Window& _window, SDL_FRect _rect) const {
    switch (state) {
    case Air:
        _window.setDrawColor(WHITE);
        _window.drawRect(_rect);
        break;

    case Heater:
        _window.blit(_window.getTexture(Textures::Heater), _rect);
        break;

    case Wall:
        _window.blit(_window.getTexture(Textures::Wall), _rect);
        break;

    case VentUp:
        _window.blit(_window.getTexture(Textures::Vent), _rect);
        break;

    case VentRight:
        _window.blit(_window.getTexture(Textures::Vent), 90.0, _rect);
        break;

    case VentDown:
        _window.blit(_window.getTexture(Textures::Vent), 180.0, _rect);
        break;

    case VentLeft:
        _window.blit(_window.getTexture(Textures::Vent), 270.0, _rect);
        break;
    
    default:
        break;
    }
}

void Cell::blitThermal(const Window& _window, SDL_FRect _rect) const {
    // Check, if cell can has pressure
    if (isWall()) {
        blitNormal(_window, _rect);
    } else {
        if (temperature < 0) {
            _window.setDrawColor({0, 0, 0, 255});
        } else if (temperature < 100.0) {
            _window.setDrawColor({Uint8(temperature*2.5f), 0, 0, 255});
        } else {
            _window.setDrawColor({255, 0, 0, 255});
        }
        _window.drawRect(_rect);
    }
}

void Cell::blitPressure(const Window& _window, SDL_FRect _rect) const {
    // Check, if cell can has pressure
    if (isWall()) {
        blitNormal(_window, _rect);
    } else {
        if (pressure > 2.54) {
            _window.setDrawColor({0, 0, 255, 255});
        } else {
            _window.setDrawColor({0, 0, Uint8(pressure*100.0f), 255});
        }
        _window.drawRect(_rect);
    }
}
