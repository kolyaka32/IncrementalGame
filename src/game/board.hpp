/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cell.hpp"


// Possible states of current showing
enum class ShowState {
    Normal,
    Thermal,
    Pressure,
};

// Main object
class Board {
 private:
    static const int height = 20, width = 20;
    Cell currentBoard[height*width];
    Cell newBoard[height*width];
    SDL_FRect firstRect = {100.0, 20.0, 40.0, 40.0};

    int pressed = 0;

 public:
    Board();
    void reset();

    void blitNormal(const Window& window) const;
    void blitThermal(const Window& window) const;
    void blitPressure(const Window& window) const;
    void blitLines(const Window& window) const;
};
