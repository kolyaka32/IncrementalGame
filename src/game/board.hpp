/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "ball.hpp"


//
class Board {
 private:
    Grid grid;
    const int count;
    std::vector<Ball> balls;
    Ball* selected = nullptr;
    SDL_FPoint lastPoint = {0, 0};
    int pressed = 0;
    SDL_FRect sides = {50, 50, 1000, 1000};

 public:
    Board(int count);
    ~Board();
    void reset();

    // Interacting with scale and position
    void clickBoard(const Mouse _mouse);
    void updateBoard(const Mouse _mouse);
    void unclickBoard(const Mouse _mouse);
    void scroll(float wheelY);

    // Billiard-specified options
    void clickBilliard(const Mouse _mouse);
    void unclickBilliard(const Mouse _mouse);
    void checkWallsCollisions();
    void checkCollisionBilliard();
    void blitBoard(const Window& window) const;

    // Gravity specified options
    void applyGravity(const Mouse _mouse);
    void checkCollisionGravity();

    // General options
    void updatePositions();
    void blitBalls(const Window& window) const;
};
