/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "fontsNames.hpp"

// Check, if use fonts
#if (USE_SDL_FONT) && (PRELOAD_FONTS)

// File names of the corresponding fonts
const char* fontsFilesNames[unsigned(Fonts::Count)] = {
    "fnt/PTSans-Regular.ttf",
};

#endif // (USE_SDL_FONT) && (PRELOAD_FONTS)
