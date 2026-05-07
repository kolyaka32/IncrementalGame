/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "board.hpp"


// Possible states of current showing
enum class ShowState {
    Normal,
    Thermal,
    Pressure,
};

// Class for interact with and visualise board
class BoardInteracter : GUI::Template {
private:
    static Board board;
    static ShowState state;
    int mousePress;  // State for pressing mouse from SDL_MouseButtonFlags

    // Rects of local positions of board
    const SDL_FRect cellRect;
    const SDL_FRect boardBackground;

    // Graphical part
    GUI::RectBackplate panelBackplate;
    GUI::HighlightedStaticText modeText;
    GUI::SwitchBox modeSwitchBox;
    GUI::DynamicText pickedPressure;
    GUI::DynamicText pickedTemperature;
    GUI::TextButton resetButton;

public:
    BoardInteracter(const Window& window, float boardX, float boardY, float panelW);

    void reset();

    // Interacting with scale and position
    void click(const Mouse mouse);
    void update(const Mouse mouse);
    void unclick(const Mouse mouse);
    void scroll(const Mouse mouse, float wheelY);

    void blit() const;
};
