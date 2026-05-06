/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "boardInteracter.hpp"


// Static objects
Board BoardInteracter::board{};
ShowState BoardInteracter::state = ShowState::Normal;

BoardInteracter::BoardInteracter(const Window& _window)
: Template(_window) {}

void BoardInteracter::reset() {
    board.reset();
}

void BoardInteracter::click(const Mouse _mouse) {
    // Start camera movement
    if (_mouse.getState() & SDL_BUTTON_MMASK) {
        grid.click(_mouse.getX(), _mouse.getY());
    }
}

void BoardInteracter::unclick(const Mouse _mouse) {
    // Applying camera movement
    grid.unClick(_mouse.getX(), _mouse.getY());
}

void BoardInteracter::scroll(const Mouse _mouse, float _wheelY) {
    grid.zoom(_wheelY, _mouse);
}

void BoardInteracter::update(const Mouse _mouse) {
    grid.update(_mouse.getX(), _mouse.getY());
}

void BoardInteracter::blit() const {
    switch (state) {
    case ShowState::Normal:
        board.blitNormal(window);
        break;

    case ShowState::Thermal:
        board.blitNormal(window);
        break;

    case ShowState::Pressure:
        board.blitNormal(window);
        break;

    default:
        break;
    }
    board.blitLines(window);
}
