/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"


Board::Board() {
    reset();
}

void Board::reset() {
    SDL_srand(getTime());
    for (int i=0; i < height*width; ++i) {
        currentBoard[i].reset();
    }
}

void Board::blitNormal(const Window& _window) const {
    SDL_FRect rect = grid.absolute(firstRect);
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            currentBoard[y*width+x].blitNormal(_window, rect);
            rect.x += rect.w;
        }
        rect.x -= rect.w * width;
        rect.y += rect.h;
    }
}

void Board::blitThermal(const Window& _window) const {
    SDL_FRect rect = grid.absolute(firstRect);
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            currentBoard[y*width+x].blitThermal(_window, rect);
            rect.x += rect.w;
        }
        rect.x -= rect.w * width;
        rect.y += rect.h;
    }
}

void Board::blitPressure(const Window& _window) const {
    SDL_FRect rect = grid.absolute(firstRect);
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            currentBoard[y*width+x].blitPressure(_window, rect);
            rect.x += rect.w;
        }
        rect.x -= rect.w * width;
        rect.y += rect.h;
    }
}

void Board::blitLines(const Window& _window) const {
    // Draw separating lines
    _window.setDrawColor(BLACK);
    const SDL_FRect rect = grid.absolute(firstRect);
    // Opposite side from corner
    const SDL_FPoint oppositeP = grid.absolute(SDL_FPoint{firstRect.x + firstRect.w * width,
        firstRect.y + firstRect.h * height});

    // Vertical lines
    float x = rect.x;
    for (int i=0; i <= width; ++i) {
        _window.drawLine(x, rect.y, x, oppositeP.y);
        x += rect.w;
    }

    // Horizontal lines
    float y = rect.y;
    for (int i=0; i <= height; ++i) {
        _window.drawLine(rect.x, y, oppositeP.x, y);
        y += rect.h;
    }
}
