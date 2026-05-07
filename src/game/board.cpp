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
        cells[i].reset();
    }
}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

void Board::applyPressure(SDL_Point _pos, float _pressure) {
    cells[_pos.y*width+_pos.x].applyPressure(_pressure);
}

void Board::applyTemperature(SDL_Point _pos, float _temperature) {
    cells[_pos.y*width+_pos.x].applyTemperature(_temperature);
}

void Board::update() {
    Cell newCells[height*width];
}

void Board::blitNormal(const Window& _window, SDL_FRect _cellRect) const {
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            cells[y*width+x].blitNormal(_window, _cellRect);
            _cellRect.x += _cellRect.w;
        }
        _cellRect.x -= _cellRect.w * width;
        _cellRect.y += _cellRect.h;
    }
}

void Board::blitThermal(const Window& _window, SDL_FRect _cellRect) const {
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            cells[y*width+x].blitThermal(_window, _cellRect);
            _cellRect.x += _cellRect.w;
        }
        _cellRect.x -= _cellRect.w * width;
        _cellRect.y += _cellRect.h;
    }
}

void Board::blitPressure(const Window& _window, SDL_FRect _cellRect) const {
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width; ++x) {
            cells[y*width+x].blitPressure(_window, _cellRect);
            _cellRect.x += _cellRect.w;
        }
        _cellRect.x -= _cellRect.w * width;
        _cellRect.y += _cellRect.h;
    }
}

void Board::blitLines(const Window& _window, SDL_FRect _cellRect) const {
    // Draw separating lines
    _window.setDrawColor(BLACK);
    // Fining opposite side
    const SDL_FPoint oppositeP = {_cellRect.x + _cellRect.w*width,
        _cellRect.y + _cellRect.h*height};   

    // Vertical lines
    float x = _cellRect.x;
    for (int i=0; i <= width; ++i) {
        _window.drawLine(x, _cellRect.y, x, oppositeP.y);
        x += _cellRect.w;
    }

    // Horizontal lines
    float y = _cellRect.y;
    for (int i=0; i <= height; ++i) {
        _window.drawLine(_cellRect.x, y, oppositeP.x, y);
        y += _cellRect.h;
    }
}
