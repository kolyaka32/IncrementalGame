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
    Cell currentBoard[height*width];
    Cell newBoard[height*width];
    const SDL_FRect firstRect;

    int pressed = 0;

 public:
    Board(float X, float Y, float side);
    void reset();

    void blitNormal(const Window& window) const;
    void blitThermal(const Window& window) const;
    void blitPressure(const Window& window) const;
    void blitLines(const Window& window) const;
};
