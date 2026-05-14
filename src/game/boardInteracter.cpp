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
holdingCell{},
holdingCellRect{0.0f, 0.0f, cellRect.w, cellRect.h},
panelBackplate(_window, _panelW/2, 0.5, _panelW, 1.0, 2.0, GREY, BLACK),
modeText(_window, _panelW/2, 0.15, {"Show mode:", "Режим отображения:"}, 1),
modeSwitchBox(_window, _panelW/2, 0.185, 0.2, {{"Elements", "Элементы"},
    {"Thermal", "Температурный"}, {"Pressure", "Давление"}}),
pickedPressure(_window, _panelW/2, 0.3, {"Pressure:%f", "Давление:%f"}, Height::Main, BLACK),
pickedTemperature(_window, _panelW/2, 0.33, {"Temperature:%.1f", "Температура:%.1f"}, Height::Main, BLACK),
buildText(_window, _panelW/2, 0.5, {"Build object:", "Объект постройки:"}, 1),
buildSwitchBox(_window, _panelW/2, 0.535, 0.2, {{"Not selected", "Не выбран"},
    {"Demplish", "Снести"}, {"Wall", "Стена"}, {"Vent", "Вентилятор"}, {"Heater", "Нагреватель"}}),
resetButton(_window, _panelW/2, 0.8, {"Reset", "Сброс"}) {}

void BoardInteracter::reset() {
    board.reset();
    mousePress = 0;
    pickedPressure.setValues(0.0f);
    pickedTemperature.setValues(0.0f);
}

void BoardInteracter::click(const Mouse _mouse) {
    // Check, if in interface part
    if (panelBackplate.in(_mouse)) {
        // Check, if changing show mode
        if (modeSwitchBox.click(_mouse)) {
            state = ShowState(modeSwitchBox.getValue());
        }
        // Update building menu
        if (buildSwitchBox.click(_mouse)) {
            // Selecting holding cell
            switch (buildSwitchBox.getValue()) {
            case 1:
                holdingCell.state = Cell::Buldozer;
                break;

            case 2:
                holdingCell.state = Cell::Wall;
                break;

            case 3:
                holdingCell.state = Cell::VentUp;
                break;

            case 4:
                holdingCell.state = Cell::Heater;
                break;

            default:
                break;
            }
        }
        // Check, if reset
        if (resetButton.in(_mouse)) {
            board.reset();
            return;
        }
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

bool BoardInteracter::press(SDL_Keycode _key) {
    if (_key == SDLK_ESCAPE) {
        // Check, if escape from any of submenus
        if (buildSwitchBox.getValue() != 0) {
            buildSwitchBox.set(0);
            return true;
        }
    }
    return false;
}

void BoardInteracter::update(const Mouse _mouse) {
    // Check, if building
    if (buildSwitchBox.getValue() != 0) {
        holdingCellRect.x = _mouse.getX() - holdingCellRect.w/2;
        holdingCellRect.y = _mouse.getY() - holdingCellRect.h/2;
    }

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

        // Check pressing on field
        switch (mousePress) {
        case SDL_BUTTON_LMASK:
            // Check, if try to do build
            switch (buildSwitchBox.getValue()) {
            case 1:
                board.setCell(position, Cell::Air);
                board.resetCell(position);
                break;

            case 2:
                board.setCell(position, Cell::Wall);
                break;

            case 3:
                board.setCell(position, Cell::VentUp);
                break;

            case 4:
                board.setCell(position, Cell::Heater);
                break;

            default:
                board.applyPressure(position, 0.2);
                break;
            }
            break;

        case SDL_BUTTON_RMASK:
            board.applyTemperature(position, 10.0);
            break;

        case SDL_BUTTON_X1MASK:
            board.applyPressure(position, -4.0);
            break;

        case SDL_BUTTON_X2MASK:
            board.applyTemperature(position, -10.0);
            break;
        
        default:
            break;
        }
        // Update showing parameter
        pickedPressure.setValues(board.getPressure(position));
        pickedTemperature.setValues(board.getTemperature(position));
    } else {
        pickedPressure.setValues(0.0f);
        pickedTemperature.setValues(0.0f);
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

    // Panel interface
    panelBackplate.blit();
    modeText.blit();
    modeSwitchBox.blit();
    pickedPressure.blit();
    pickedTemperature.blit();
    buildText.blit();
    buildSwitchBox.blit();
    resetButton.blit();

    // Building
    if (buildSwitchBox.getValue() != 0) {
        holdingCell.blitNormal(window, holdingCellRect);
    }
}
