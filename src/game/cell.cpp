/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cell.hpp"


Cell::Cell() {}

void Cell::reset() {
    state = Air;
    gase.reset();
}

bool Cell::isWall() const {
    return state & wallMask;
}

bool Cell::isVent() const {
    return state & stateMask == VentUp;
}

void Cell::applyPressure(float _pressure) {
    if (!isWall()) {
        gase.applyPressure(_pressure);
    }
}

void Cell::applyTemperature(float _temperature) {
    if (!isWall()) {
        gase.applyTemperature(_temperature);
    }
}

void Cell::heatUpTo(Cell& _dest, float _targetTemp) const {
    gase.heatUpTo(_dest.gase, _targetTemp);
}

float Cell::getPressure() const {
    return gase.getPressure();
}

float Cell::getTemperature() const {
    return gase.getTemperature();
}

void Cell::exchange(const Cell& _src2, Cell& _dst1, Cell& _dst2) const {
    if (!isWall() && !_src2.isWall()) {
        gase.exchange(_src2.gase, _dst1.gase, _dst2.gase);
    }
}

void Cell::exchange(Cell& _dest) const {
    if (!isWall()) {
        gase.exchange(_dest.gase);
    }
}

void Cell::vent(const Cell& _srcIn, const Cell& _srcOut, Cell& _dstIn, Cell& _dstOut) const {
    if (!_srcIn.isWall() && !_srcOut.isWall()) {
        _srcIn.gase.vent(_srcOut.gase, _dstIn.gase, _dstOut.gase, 0.2);
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

    case Buldozer:
        _window.blit(_window.getTexture(Textures::Buldozer), _rect);
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
        gase.blitThermal(_window, _rect);
    }
}

void Cell::blitPressure(const Window& _window, SDL_FRect _rect) const {
    // Check, if cell can has pressure
    if (isWall()) {
        blitNormal(_window, _rect);
    } else {
        gase.blitPressure(_window, _rect);
    }
}
