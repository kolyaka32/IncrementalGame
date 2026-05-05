/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/board.hpp"


// Cycle with game with gravity
class GravityCycle : public BaseCycle {
 protected:
    // Active game part
    Board field;

    // New overrided cycle functions
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputMouseWheel(float _wheelY) override;
    void inputKeys(SDL_Keycode _key) override;
    void update() override;
    void draw() const override;

 public:
    GravityCycle(Window& _window);
};
