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

void Cell::update() {
    //ux *= speed;
    //uy *= speed;
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
    _window.setDrawColor({Uint8(temperature*2), 0, 0, 255});
    _window.drawRect(_rect);
}

void Cell::blitPressure(const Window& _window, SDL_FRect _rect) const {
    _window.setDrawColor({0, 0, Uint8(pressure*2), 255});
    _window.drawRect(_rect);
}
