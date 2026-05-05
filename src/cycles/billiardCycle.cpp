/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "billiardCycle.hpp"
#include "selectCycle.hpp"


BilliardCycle::BilliardCycle(Window& _window)
: BaseCycle(_window),
field(200) {
    if (!isRestarted()) {
        // Resetting field
        field.reset();
    }
}

bool BilliardCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    field.clickBoard(mouse);
    field.clickBilliard(mouse);
    return false;
}

void BilliardCycle::inputMouseUp() {
    mouse.updatePos();
    field.unclickBoard(mouse);
    field.unclickBilliard(mouse);
    settings.unClick();
}

void BilliardCycle::inputMouseWheel(float _wheelY) {
    BaseCycle::inputMouseWheel(_wheelY);
    field.scroll(_wheelY);
}

void BilliardCycle::inputKeys(SDL_Keycode _key) {
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

void BilliardCycle::update() {
    BaseCycle::update();

    Mouse mouse{};
    mouse.updatePos();

    field.updateBoard(mouse);
    field.checkCollisionBilliard();
    field.checkWallsCollisions();
    field.updatePositions();
}

void BilliardCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blitBoard(window);
    field.blitBalls(window);

    // Drawing upper dashboard
    exitButton.blit();
    settings.blit();

    // Bliting all to screen
    window.render();
}
