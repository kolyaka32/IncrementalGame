/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"
#include "navigation.hpp"


//
class Cell {
 private:
    float pressure;
    float temperature;

 public:
    Cell();
    void reset();
    bool isSelected(SDL_FPoint point) const;
    void update();
    void blit(const Window& window, SDL_FRect rect) const;
};
