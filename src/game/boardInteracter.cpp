/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "boardInteracter.hpp"


// Static objects
Board BoardInteracter::board;
ShowState BoardInteracter::state = ShowState::Normal;

BoardInteracter::BoardInteracter(const Window& _window, float _boardX, float _boardY, float _panelW)
: Template(_window),
cellRect{_boardX*_window.getWidth(), _boardY*_window.getHeight(), 40.0f, 40.0f},
boardBackground{cellRect.x, cellRect.y, cellRect.w*board.getWidth(), cellRect.h*board.getHeight()},
panelBackplate(_window, _panelW/2, 0.5, _panelW, 1.0, 2.0, GREY, BLACK),
modeText(_window, _panelW/2, 0.15, {"Show mode:", "Режим отображения:"}, 1),
modeSwitchBox(_window, _panelW/2, 0.2, 0.2, {{"Elements", "Элементы"},
    {"Thermal", "Температурный"}, {"Pressure", "Давление"}}) {}

void BoardInteracter::reset() {
    board.reset();
    mousePress = 0;
}

void BoardInteracter::click(const Mouse _mouse) {
    // Check, if in interface part
    if (panelBackplate.in(_mouse)) {
        // Check, if changing show mode
        if (modeSwitchBox.click(_mouse)) {
            state = ShowState(modeSwitchBox.getValue());
            return;
        }
        // Check, if dragging item
        // !
        return;
    }
    // Check, if start interaction
    mousePress = _mouse.getState();

    // Start camera movement
    if (mousePress == SDL_BUTTON_MMASK) {
        grid.click(_mouse.getX(), _mouse.getY());
    }
}

void BoardInteracter::unclick(const Mouse _mouse) {
    // Resetting movement
    mousePress = 0;
}

void BoardInteracter::scroll(const Mouse _mouse, float _wheelY) {
    grid.zoom(_wheelY, _mouse);
}

void BoardInteracter::update(const Mouse _mouse) {
    if (mousePress == SDL_BUTTON_MMASK) {
        grid.update(_mouse.getX(), _mouse.getY());
    }

    // Finding absolute position of background
    SDL_FRect backgroundRect = grid.absolute(boardBackground);

    // If click on field
    if (_mouse.in(backgroundRect)) {
        // Finding connected cell
        const SDL_FRect rect = grid.absolute(cellRect);
        SDL_Point position = {int((_mouse.getX()-rect.x)/rect.w), int((_mouse.getY()-rect.y)/rect.h)};

        if (mousePress == SDL_BUTTON_LMASK) {
            board.applyPressure(position, 10.0);
        }
        if (mousePress == SDL_BUTTON_RMASK) {
            board.applyTemperature(position, 100.0);
        }
    }

    // Updating physic
    board.update();
}

void BoardInteracter::blit() const {
    // Get rect of first cell
    const SDL_FRect rect = grid.absolute(cellRect);

    // Draw board
    switch (state) {
    case ShowState::Normal:
        board.blitNormal(window, rect);
        break;

    case ShowState::Thermal:
        board.blitThermal(window, rect);
        break;

    case ShowState::Pressure:
        board.blitPressure(window, rect);
        break;

    default:
        break;
    }
    board.blitLines(window, rect);

    // Paanel interface
    panelBackplate.blit();
    modeText.blit();
    modeSwitchBox.blit();
}
