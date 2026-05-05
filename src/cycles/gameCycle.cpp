/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"


GameCycle::GameCycle(Window& _window)
: BaseCycle(_window),
field(2000) {
    if (!isRestarted()) {
        // Resetting field
        field.reset();
    }
}

bool GameCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    field.clickBoard(mouse);
    return false;
}

void GameCycle::inputMouseUp() {
    mouse.updatePos();
    field.unclickBoard(mouse);
    settings.unClick();
}

void GameCycle::inputMouseWheel(float _wheelY) {
    BaseCycle::inputMouseWheel(_wheelY);
    field.scroll(_wheelY);
}

void GameCycle::inputKeys(SDL_Keycode _key) {
    // Quiting to menu
    if (_key == SDLK_Q) {
        stop();
    }
    if (_key == SDLK_ESCAPE) {
        // Closing top open object
        settings.activate();
        return;
    }
}

void GameCycle::update() {
    BaseCycle::update();

    Mouse mouse{};
    mouse.updatePos();

    field.updateBoard(mouse);
    field.applyGravity(mouse);
    field.checkCollisionGravity();
    field.updatePositions();
}

void GameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blitBalls(window);

    // Drawing upper dashboard
    exitButton.blit();
    settings.blit();

    // Bliting all to screen
    window.render();
}
