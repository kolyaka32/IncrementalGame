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

    switch (state) {
    case ShowState::Normal:
        for (int y=0; y < height; ++y) {
            for (int x=0; x < width; ++x) {
                currentBoard[y*width+x].blitNormal(_window, rect);
                rect.x += rect.w;
            }
            rect.x -= rect.w * width;
            rect.y += rect.h;
        }
        break;

    case ShowState::Thermal:
        for (int y=0; y < height; ++y) {
            for (int x=0; x < width; ++x) {
                currentBoard[y*width+x].blitThermal(_window, rect);
                rect.x += rect.w;
            }
            rect.x -= rect.w * width;
            rect.y += rect.h;
        }
        break;

    case ShowState::Pressure:
        for (int y=0; y < height; ++y) {
            for (int x=0; x < width; ++x) {
                currentBoard[y*width+x].blitPressure(_window, rect);
                rect.x += rect.w;
            }
            rect.x -= rect.w * width;
            rect.y += rect.h;
        }
        break;
    
    default:
        break;
    }

    // Draw separating lines
    _window.setDrawColor(BLACK);
    const SDL_FPoint cornerP = grid.absolute(SDL_FPoint{firstRect.x, firstRect.y});
    // Opposite side from corner
    const SDL_FPoint oppositeP = grid.absolute(SDL_FPoint{firstRect.x + firstRect.w * width,
        firstRect.y + firstRect.h * height});

    // Vertical lines
    float x = cornerP.x;
    for (int i=0; i <= width; ++i) {
        _window.drawLine(x, cornerP.y, x, oppositeP.y);
        x += rect.w;
    }
    // Horizontal lines
    float y = cornerP.y;
    for (int i=0; i <= height; ++i) {
        _window.drawLine(cornerP.x, y, oppositeP.x, y);
        y += rect.h;
    }
}
