/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "boardInteracter.hpp"


// Static objects
Board BoardInteracter::board{300.0, 50.0, 40.0};
ShowState BoardInteracter::state = ShowState::Normal;

BoardInteracter::BoardInteracter(const Window& _window)
: Template(_window),
backplate(_window, 0.12, 0.5, 0.24, 1.0, 2.0, GREY, BLACK),
modeText(_window, 0.12, 0.15, {"Show mode:", "Режим отображения:"}, 1),
modeSwitchBox(_window, 0.12, 0.2, 0.2, {{"Elements", "Элементы"},
    {"Thermal", "Температурный"}, {"Pressure", "Давление"}}) {}

void BoardInteracter::reset() {
    board.reset();
}

void BoardInteracter::click(const Mouse _mouse) {
    // Check, if in interface part
    if (backplate.in(_mouse)) {
        if (modeSwitchBox.click(_mouse)) {
            state = ShowState(modeSwitchBox.getValue());
            return;
        }
        return;
    }

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
    // Draw board
    switch (state) {
    case ShowState::Normal:
        board.blitNormal(window);
        break;

    case ShowState::Thermal:
        board.blitThermal(window);
        break;

    case ShowState::Pressure:
        board.blitPressure(window);
        break;

    default:
        break;
    }
    board.blitLines(window);

    // Interface
    backplate.blit();
    modeText.blit();
    modeSwitchBox.blit();
}
