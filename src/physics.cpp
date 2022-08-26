#include "physics.hpp"

#include "windows.hpp"

WindowPosition screenToBoxCoords(
    const WindowPosition& windowPosition,
    const WindowSize&     windowSize) {
	return {
	    static_cast<uint16_t>(windowPosition.x + (windowSize.width / 2)),
	    static_cast<uint16_t>(windowPosition.y + (windowSize.height / 2))};
}

WindowPosition boxToScreenCoords(
    const WindowPosition& windowPosition,
    const WindowSize&     windowSize) {
	return {
	    static_cast<uint16_t>(windowPosition.x - (windowSize.width / 2)),
	    static_cast<uint16_t>(windowPosition.y - (windowSize.height / 2))};
}
