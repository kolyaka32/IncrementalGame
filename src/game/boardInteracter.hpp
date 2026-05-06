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

    // Graphical part
    GUI::RectBackplate backplate;
    GUI::HighlightedStaticText modeText;
    GUI::SwitchBox modeSwitchBox;

public:
    BoardInteracter(const Window& window);

    void reset();

    // Interacting with scale and position
    void click(const Mouse mouse);
    void update(const Mouse mouse);
    void unclick(const Mouse mouse);
    void scroll(const Mouse mouse, float wheelY);

    void blit() const;
};
