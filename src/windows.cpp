#include "windows.hpp"

#include "utils.hpp"

#include <iostream>
#include <string>
#include <vector>

std::string setWindowSize(const int& id, const uint16_t& width, const uint16_t& height) {
	return exec(("xdotool windowsize \"" + std::to_string(id) + "\" " +
		     std::to_string(width) + " " + std::to_string(height))
			.c_str());
}

std::string setWindowPosition(const int& id, const uint16_t& x, const uint16_t& y) {
	return exec(("xdotool windowmove \"" + std::to_string(id) + "\" " +
		     std::to_string(x) + " " + std::to_string(y))
			.c_str());
}

std::pair<WindowPosition, WindowSize> getWindowProperties(const int& id) {
	std::pair<WindowPosition, WindowSize> ret;

	auto output = exec(("xwininfo -id " + std::to_string(id)).c_str());

	for(auto& line: split(output, "\n")) {
		if(line.starts_with("  Absolute upper-left X:  ")) {
			ret.first.x = stoi(line.substr(24, line.size() - 1));
		} else if(line.starts_with("  Absolute upper-left Y:  ")) {
			ret.first.y = stoi(line.substr(24, line.size() - 1));
		} else if(line.starts_with("  Width: ")) {
			ret.second.width = stoi(line.substr(9, line.size() - 1));
		} else if(line.starts_with("  Height: ")) {
			ret.second.height = stoi(line.substr(10, line.size() - 1));
			break;
		}
	}

	return ret;
}

WindowPosition getWindowPosition(const int& id) {
	WindowPosition ret;
	auto           output = exec(("xwininfo -id " + std::to_string(id)).c_str());

	for(auto& line: split(output, "\n")) {
		if(line.starts_with("  Absolute upper-left X:  ")) {
			ret.x = stoi(line.substr(24, line.size() - 1));
		} else if(line.starts_with("  Absolute upper-left Y:  ")) {
			ret.y = stoi(line.substr(24, line.size() - 1));
			break;
		}
	}

	return ret;
}

WindowSize getWindowSize(const int& id) {
	WindowSize ret;
	auto       output = exec(("xwininfo -id " + std::to_string(id)).c_str());

	for(auto& line: split(output, "\n")) {
		if(line.starts_with("  Width: ")) {
			ret.width = stoi(line.substr(9, line.size() - 1));
		} else if(line.starts_with("  Height: ")) {
			ret.height = stoi(line.substr(10, line.size() - 1));
			break;
		}
	}

	return ret;
}

std::vector<MyWindow> getWindowsOnWorkspace(const std::string& workspace) {
	std::vector<MyWindow> ret;

	std::string_view wmctrl       = "/usr/bin/wmctrl -l";
	std::string      wmctrlOutput = exec(wmctrl.data());

	for(auto& line: split(wmctrlOutput, "\n")) {
		if(line != "") {
			auto ws = split(line, " ");
			if(trim(ws[2]) == workspace) {
				std::cout << "id: " << ws[0] << "\n";
				auto id = std::stoi(ws[0], nullptr, 16);
				std::cout << "id: " << id << "\n";

				auto props = getWindowProperties(id);

				// clang-format off
				ret.push_back({
					line.substr(36, line.size() - 1), // WARN: FIX THAT HARDCODING
					id,
					props.first,
					props.second
				});
				// clang-format on
			}
		}
	}

	return ret;
}
