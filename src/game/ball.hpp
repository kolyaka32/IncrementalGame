/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"
#include "navigation.hpp"


//
class Ball {
 private:
    const float diameter = 20.0;
    const float friction = 0;
    const float speed = 0.99;
    const float G = 1;
    SDL_FRect dest;
    float ux = 0.0, uy = 0.0;

 public:
    Ball();
    void set(SDL_FPoint point);
    void setSpeed(float ux, float uy);
    void pull(SDL_FPoint point);
    void push(SDL_FPoint point);
    bool isSelected(SDL_FPoint point) const;
    void update();
    void checkWalls(SDL_FRect rect);
    void checkCollisionBilliard(Ball& ball);
    void checkCollisionGravity(Ball& ball);
    void blit(const Window& window, const Grid grid) const;
};
