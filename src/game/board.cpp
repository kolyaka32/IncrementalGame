/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"


Board::Board(int _count)
: count(_count) {
    // Create first placement
    for (int i=0; i < count; ++i) {
        balls.push_back(Ball());
    }
    reset();
}

Board::~Board() {
    balls.clear();
}

void Board::reset() {
    SDL_srand(getTime());
    for (int i=0; i < count; ++i) {
        balls[i].set(grid.absolute(SDL_FPoint{SDL_randf()*sides.w + sides.x,
            SDL_randf()*sides.h + sides.y}));
    }
}

void Board::clickBoard(const Mouse _mouse) {
    // Start camera movement
    if (_mouse.getState() & SDL_BUTTON_MMASK) {
        grid.click(_mouse.getX(), _mouse.getY());
    }
}

void Board::scroll(float _wheelY) {
    Mouse mouse{};
    mouse.updatePos();

    grid.zoom(_wheelY, mouse);
}

void Board::updateBoard(const Mouse _mouse) {
    grid.update(_mouse.getX(), _mouse.getY());
}

void Board::unclickBoard(const Mouse _mouse) {
    // Applying camera movement
    grid.unClick(_mouse.getX(), _mouse.getY());
}


void Board::clickBilliard(const Mouse _mouse) {
    // Finding nearest ball
    selected = nullptr;
    SDL_FPoint current = grid.local(_mouse);
    if (_mouse.getState() & SDL_BUTTON_LMASK) {
        for (int i=0; i < count; ++i) {
            if (balls[i].isSelected(current)) {
                selected = &balls[i];
                lastPoint = current;
                logAdditional("Selected %d", i);
                return;
            }
        }
    }
}

void Board::unclickBilliard(const Mouse _mouse) {
    // Launching selected ball
    if (selected) {
        SDL_FPoint current = grid.local(_mouse);
        selected->setSpeed(current.x - lastPoint.x, current.y - lastPoint.y);
    }
}

void Board::checkWallsCollisions() {
    for (int i=0; i < count; ++i) {
        balls[i].checkWalls(sides);
    }
}

void Board::checkCollisionBilliard() {
    for (int i=0; i < count; ++i) {
        for (int j=1+i; j < count; ++j) {
            balls[i].checkCollisionBilliard(balls[j]);
        }
    }
}

void Board::blitBoard(const Window& _window) const {
    _window.blit(_window.getTexture(Textures::Board), grid.absolute(sides));
}


void Board::applyGravity(const Mouse _mouse) {
    if (_mouse.getState() & SDL_BUTTON_LMASK) {
        // Appling push to all
        for (int i=0; i < count; ++i) {
            balls[i].push(grid.local(_mouse));
        }
    }
    if (_mouse.getState() & SDL_BUTTON_RMASK) {
        // Appling pull to all
        for (int i=0; i < count; ++i) {
            balls[i].pull(grid.local(_mouse));
        }
    }
}

void Board::checkCollisionGravity() {
    for (int i=0; i < count; ++i) {
        for (int j=1+i; j < count; ++j) {
            balls[i].checkCollisionGravity(balls[j]);
        }
    }
}


void Board::updatePositions() {
    for (int i=0; i < count; ++i) {
        balls[i].update();
    }
}

void Board::blitBalls(const Window& _window) const {
    for (int i=0; i < count; ++i) {
        balls[i].blit(_window, grid);
    }
}
