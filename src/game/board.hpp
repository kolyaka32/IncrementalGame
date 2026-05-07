/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cell.hpp"


// Main object
class Board {
 private:
    static const int height = 20, width = 20;
    Cell cells[height*width];

 public:
    Board();
    void reset();
    int getWidth() const;
    int getHeight() const;

    // Interaction
    void applyPressure(SDL_Point pos, float pressure);
    void applyTemperature(SDL_Point pos, float temperature);
    void update();

    void blitNormal(const Window& window, SDL_FRect cellRect) const;
    void blitThermal(const Window& window, SDL_FRect cellRect) const;
    void blitPressure(const Window& window, SDL_FRect cellRect) const;
    void blitLines(const Window& window, SDL_FRect cellRect) const;
};
