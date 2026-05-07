/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"
#include "navigation.hpp"


//
class Cell {
 public:
    enum State : Uint8 {
        Air,
        Wall,
        VentUp,
        VentRight,
        VentDown,
        VentLeft,
    };

 private:
    State state = Air;
    float pressure;
    float temperature;

 public:
    Cell();
    void reset();

    // Interactions
    void update(const Cell& src2, Cell& dst1, Cell& dst2) const;  // Interact between 2 cell with saving to nother place
    void applyPressure(float pressure);
    void applyTemperature(float temperature);

    // Drawing
    void blitNormal(const Window& window, SDL_FRect rect) const;
    void blitThermal(const Window& window, SDL_FRect rect) const;
    void blitPressure(const Window& window, SDL_FRect rect) const;
};
