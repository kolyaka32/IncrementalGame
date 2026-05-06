/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::SwitchBox::SwitchBox(const Window& _window, float _X, float _Y, float _W,
    std::initializer_list<LanguagedText> _texts, unsigned _startOption, float _size, Color _color)
: Template(_window),
height(_size*1.2f) {
    // Setting background
    background = {(_X-_W/2)*window.getWidth(), _Y*window.getHeight()-height/2, _W*window.getWidth(), height};

    // Placing select options
    for (const LanguagedText* text=_texts.begin(); text != _texts.end(); ++text) {
        drawnTexts.emplace_back(_window, _X, _Y, std::move(*text), _size, _color, GUI::Aligment::Left);
    }
    // Updating start option
    selected = _startOption;

    // Creating arrow
    arrowRect = {background.x, background.y, height, height};
    arrowTexture = window.createTexture(arrowRect.w, arrowRect.h);
    SDL_Vertex vertex[3] = {
        {  // Down point
            {_X+arrowRect.w*0.5f, _Y+arrowRect.h*0.8f},
            {0.0, 0.0, 0.0, 1.0},  // Black
        },
        {  // Left point
            {_X+arrowRect.w*0.1f, _Y+arrowRect.h*0.1f},
            {0.0, 0.0, 0.0, 1.0},  // Black
        },
        {  // Right point
            {_X+arrowRect.w*0.9f, _Y+arrowRect.w*0.1f},
            {0.0, 0.0, 0.0, 1.0},  // Black
        },
    };
    window.drawGeometry(vertex, 3, arrowTexture);
    //window.resetRenderTarget();
}

void GUI::SwitchBox::set(unsigned _value) {
    if (opened) {
        selected = _value;
        opened = false;
        drawnTexts[selected].move(0.0, -selected*height);
        background.h = height;
    } else {
        // Resetting old option
        drawnTexts[selected].move(0.0, selected*height);

        // Moving new option
        selected = _value;
        drawnTexts[selected].move(0.0, -selected*height);
    }
}

unsigned GUI::SwitchBox::getValue() {
    return selected;
}

bool GUI::SwitchBox::click(const Mouse _mouse) {
    if (opened) {
        // Closing
        background.h = height;
        opened = false;
        // Selecting variant
        if (_mouse.in(background)) {
            // Finding new option
            selected = (_mouse.getY() - background.y) / height;
            drawnTexts[selected].move(0.0, -selected*height);
            return true;
        }
        // Resetting to previous
        drawnTexts[selected].move(0, -selected*height);
    } else {
        if (_mouse.in(background)) {
            // Selecting variant
            opened = true;
            background.h = height * drawnTexts.size();
            // Resetting selected postion
            drawnTexts[selected].move(0.0, selected*height);
        }
    }
    return false;
}

void GUI::SwitchBox::blit() const {
    // Drawing background
    window.setDrawColor();
    window.drawRect(background);

    // Draw open or close version depend on state
    if (opened) {
        for (int i=0; i < drawnTexts.size(); ++i) {
            drawnTexts[i].blit();
        }
    } else {
        drawnTexts[selected].blit();
    }
    window.blit(arrowTexture, arrowRect);
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
