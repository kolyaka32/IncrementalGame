/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"


Board::Board() {
    // Create first placement
    reset();
}

void Board::reset() {
    SDL_srand(getTime());
    for (int i=0; i < height*width; ++i) {
        currentBoard[i].reset();
    }
}

void Board::click(const Mouse _mouse) {
    // Start camera movement
    if (_mouse.getState() & SDL_BUTTON_MMASK) {
        grid.click(_mouse.getX(), _mouse.getY());
    }
}

void Board::unclick(const Mouse _mouse) {
    // Applying camera movement
    grid.unClick(_mouse.getX(), _mouse.getY());
}

void Board::scroll(const Mouse _mouse, float _wheelY) {
    grid.zoom(_wheelY, _mouse);
}

void Board::update(const Mouse _mouse) {
    grid.update(_mouse.getX(), _mouse.getY());
}

void Board::blit(const Window& _window) const {
    // Rect
    SDL_FRect rect = grid.absolute(firstRect);
    //_window.blit(_window.getTexture(Textures::Board), grid.absolute(sides));

    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            currentBoard[y*width+x].blit(_window, rect);
            rect.x += rect.w;
        }
        rect.x -= rect.w * width;
        rect.y += rect.h;
    }
}
