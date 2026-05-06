/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cell.hpp"


Cell::Cell() {}

void Cell::reset() {
    pressure = 0.0;
    temperature = 0.0;
}

bool Cell::isSelected(const SDL_FPoint _point) const {
    return false;
    /*(sqr(_point.x - dest.x - dest.w/2) + 
        sqr(_point.y - dest.y - dest.h/2) < diameter*diameter/4);*/
}

void Cell::update() {
    //ux *= speed;
    //uy *= speed;
}

void Cell::blit(const Window& _window, SDL_FRect _rect) const {
    _window.setDrawColor(WHITE);
    _window.drawRect(_rect);

    _window.setDrawColor({0, 0, Uint8(pressure*255), 255});
    _rect.w /= 2;
    _window.drawRect(_rect);

    _window.setDrawColor({Uint8(temperature*255), 0, 0, 255});
    _rect.x += _rect.w;
    _window.drawRect(_rect);
}
