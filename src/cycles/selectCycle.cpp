/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"
#include "billiardCycle.hpp"
#include "gravityCycle.hpp"


// Starting basic template with main theme
SelectCycle::SelectCycle(Window& _window)
: BaseCycle(_window),
titleText(window, 0.5, 0.15, {"Billiard", "Бильярд", "Billardkugel", "Більярд"}, 3, Height::Title),
billiardButton(window, 0.5, 0.4, {"Billiard mode", "Режим бильярда", "Billard-Modus", "Рэжым більярда"}),
gravityButton(window, 0.5, 0.6, {"Gravity mode", "Режим гравитации", "Schwerkraft-Modus", "Рэжым гравітацыі"}) {
    // Starting menu song (if wasn't started)
    // music.start(Music::Menu);
    logAdditional("Start select cycle");
}

// Getting selected button
bool SelectCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (billiardButton.in(mouse)) {
        runCycle<BilliardCycle>(window);
        return true;
    }
    if (gravityButton.in(mouse)) {
        runCycle<GravityCycle>(window);
        return true;
    }
    return false;
}

void SelectCycle::inputKeys(SDL_Keycode _key) {
    switch (_key) {
    case SDLK_ESCAPE:
        settings.activate();
        return;
    }
}

void SelectCycle::update() {
    BaseCycle::update();
}

void SelectCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Bliting title
    titleText.blit();

    // Blitting start buttons
    billiardButton.blit();
    gravityButton.blit();

    // Settings menu
    settings.blit();

    // Bliting all to screen
    window.render();
}
