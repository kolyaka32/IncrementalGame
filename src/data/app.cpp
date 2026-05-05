/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "cycleTemplate.hpp"


bool App::running = true;

void App::stop() {
    running = false;
    CycleTemplate::stop();
}

bool App::isRunning() {
    return running;
}
