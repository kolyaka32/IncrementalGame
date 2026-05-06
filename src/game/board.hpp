/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cell.hpp"


enum class ShowState {
    Normal,
    Thermal,
    Pressure,
};


// Main object
class Board {
 private:
    Grid grid;
    static const int height = 20, width = 20;
    Cell currentBoard[height*width];
    Cell newBoard[height*width];
    ShowState state = ShowState::Normal;
    SDL_FRect firstRect = {100.0, 20.0, 40.0, 40.0};

    int pressed = 0;

 public:
    Board();
    void reset();

    // Interacting with scale and position
    void click(const Mouse mouse);
    void update(const Mouse mouse);
    void unclick(const Mouse mouse);
    void scroll(const Mouse mouse, float wheelY);

    void blit(const Window& window) const;
};
