/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cell.hpp"


Cell::Cell() {}

void Cell::reset() {
    pressure = 0.0;
    temperature = 20.0;
}

void Cell::applyPressure(float _pressure) {
    pressure += _pressure;
}

void Cell::applyTemperature(float _temperature) {
    temperature += _temperature;
}

void Cell::exchange(const Cell& _src2, Cell& _dst1, Cell& _dst2) const {
    // Exchange only if both air
    if (state == Air && _src2.state == Air) {
        // Calculating difference (signed)
        float diff = pressure - _src2.pressure;
        float tempDiff = temperature - _src2.temperature;

        // Changing pressure
        _dst1.pressure -= diff * pressureKoef;
        _dst2.pressure += diff * pressureKoef;

        // Changing temperture
        _dst1.temperature -= tempDiff * diff * temperatureKoef;
        _dst2.temperature += tempDiff * diff * temperatureKoef;
    }
}

void Cell::blitNormal(const Window& _window, SDL_FRect _rect) const {
    switch (state) {
    case Air:
        _window.setDrawColor(WHITE);
        break;

    case Wall:
        _window.setDrawColor(DARK_GREY);
        break;

    case VentUp:
    case VentRight:
    case VentDown:
    case VentLeft:
        _window.setDrawColor(BLUE);
        break;
    
    default:
        break;
    }
    _window.drawRect(_rect);
}

void Cell::blitThermal(const Window& _window, SDL_FRect _rect) const {
    if (temperature > 63.0) {
        _window.setDrawColor({255, 0, 0, 255});
    } else {
        _window.setDrawColor({Uint8(temperature*4.0f), 0, 0, 255});
    }
    _window.drawRect(_rect);
}

void Cell::blitPressure(const Window& _window, SDL_FRect _rect) const {
    if (pressure > 2.54) {
        _window.setDrawColor({0, 0, 255, 255});
    } else {
        _window.setDrawColor({0, 0, Uint8(pressure*100.0f), 255});
    }
    _window.drawRect(_rect);
}
