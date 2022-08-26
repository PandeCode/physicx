#pragma once

#include "windows.hpp"

WindowPosition
    screenToBoxCoords(const WindowPosition& windowPosition, const WindowSize& windowSize);

WindowPosition
    boxToScreenCoords(const WindowPosition& windowPosition, const WindowSize& windowSize);
