#pragma once
#include <string>
#include <vector>

struct WindowPosition {
	uint16_t x;
	uint16_t y;
};

struct WindowSize {
	uint16_t width;
	uint16_t height;
};

struct MyWindow {
	std::string name;
	int         id;
	WindowPosition position;
	WindowSize size;
};

std::string setWindowSize(const int& id, const uint16_t& width, const uint16_t& height);

std::string setWindowPosition(const int& id, const uint16_t& x, const uint16_t& y);

std::string setWindowSize(
    const std::string& windowName,
    const uint16_t&    width,
    const uint16_t&    height);

std::string setWindowPosition(
    const std::string& windowName,
    const uint16_t&    x,
    const uint16_t&    y);

WindowPosition getWindowPosition(const int& id);

WindowSize getWindowSize(const int& id);

WindowPosition getWindowPosition(const std::string& windowName);

WindowSize getWindowSize(const std::string& windowName);

std::vector<MyWindow> getWindowsOnWorkspace(const std::string& workspace);

std::pair<WindowPosition, WindowSize> getWindowProperties(const int& id);
