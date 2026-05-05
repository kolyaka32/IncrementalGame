/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gravityCycle.hpp"
#include "selectCycle.hpp"


GravityCycle::GravityCycle(Window& _window)
: BaseCycle(_window),
field(2000) {
    if (!isRestarted()) {
        // Resetting field
        field.reset();
    }
}

bool GravityCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    field.clickBoard(mouse);
    return false;
}

void GravityCycle::inputMouseUp() {
    mouse.updatePos();
    field.unclickBoard(mouse);
    settings.unClick();
}

void GravityCycle::inputMouseWheel(float _wheelY) {
    BaseCycle::inputMouseWheel(_wheelY);
    field.scroll(_wheelY);
}

void GravityCycle::inputKeys(SDL_Keycode _key) {
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

void GravityCycle::update() {
    BaseCycle::update();

    Mouse mouse{};
    mouse.updatePos();

    field.updateBoard(mouse);
    field.applyGravity(mouse);
    field.checkCollisionGravity();
    field.updatePositions();
}

void GravityCycle::draw() const {
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
