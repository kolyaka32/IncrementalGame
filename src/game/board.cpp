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
    // Copying to temp array
    memcpy(tempCells, cells, sizeof(tempCells));
}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

void Board::setCell(SDL_Point _pos, Cell::CellState _state) {
    cells[_pos.y*width+_pos.x].setState(_state);
    tempCells[_pos.y*width+_pos.x].setState(_state);
}

void Board::resetCell(SDL_Point _pos) {
    cells[_pos.y*width+_pos.x].reset();
    tempCells[_pos.y*width+_pos.x].reset();
}

void Board::applyPressure(SDL_Point _pos, float _pressure) {
    cells[_pos.y*width+_pos.x].applyPressure(_pressure);
    tempCells[_pos.y*width+_pos.x].applyPressure(_pressure);
}

void Board::applyTemperature(SDL_Point _pos, float _temperature) {
    cells[_pos.y*width+_pos.x].applyTemperature(_temperature);
    tempCells[_pos.y*width+_pos.x].applyTemperature(_temperature);
}

float Board::getPressure(SDL_Point _pos) const {
    return cells[_pos.y*width+_pos.x].getPressure();
}

float Board::getTemperature(SDL_Point _pos) const {
    return cells[_pos.y*width+_pos.x].getTemperature();
}

void Board::update() {
    // Vertical interactions
    for (int y=0; y < height-1; ++y) {
        for (int x=0; x < width; ++x) {
            // Exchanging with cell bellow
            cells[y*width+x].exchange(cells[(y+1)*width+x],
                tempCells[y*width+x], tempCells[(y+1)*width+x]);
        }
    }

    // Horizontal interactions
    for (int y=0; y < height; ++y) {
        for (int x=0; x < width-1; ++x) {
            // Exchanging with cell right to it
            cells[y*width+x].exchange(cells[y*width+x+1],
                tempCells[y*width+x], tempCells[y*width+x+1]);
        }
    }

    // Copying saved array to main
    memcpy(cells, tempCells, sizeof(cells));
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
