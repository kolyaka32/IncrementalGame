/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "message.hpp"

#if (USE_SDL_NET)


Message::Message() {}

const Uint8* Message::getData() const {
    return data;
}

size_t Message::getLength() const {
    return size;
}

#endif  // (USE_SDL_NET)
