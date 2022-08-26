#include "box2d/box2d.h"
#include "physics.hpp"
#include "utils.hpp"
#include "windows.hpp"

#include <array>
#include <cstring>
#include <iostream>

void usage() {
	std::cout <<
	    R"(PhysicX
	--help / -h => print this message
	[uint8]     => desktop index
Example:
	PhysicX 0
)";
}
auto strToInt(auto& str) {
	try {
		return std::stoi(str);
	} catch(std::invalid_argument e) {
		std::cout << "Invalid int workspace '" << str << "'\n" << e.what();
		usage();
		exit(1);
		//return 0;
	}
}

int main(int argc, const char* argv[]) {

	if(argc < 2) {
		std::cout << "Bad Usage: " << std::endl;
		usage();
		return 1;
	} else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		usage();
	} else {
		uint16_t workspace = strToInt(argv[1]);
		std::cout << "Workspace " << workspace << std::endl;
		auto windows             = getWindowsOnWorkspace(argv[1]);

		float fps                = 60.0f;
		float timeStep           = 1.0f / fps;
		int32 velocityIterations = 6;
		int32 positionIterations = 6;

		b2Vec2  gravity(0.0f, 20.0f);
		b2World world(gravity);

		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(
		    683.0f,
		    768.0f); // TODO: REPLACE 700.0f with screen -height
		b2Body*        groundBody = world.CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(
		    683.0f,
		    1.0f); // TODO: REPLACE 683.0f with screen width/2
		groundBody->CreateFixture(&groundBox, 0.0f);

		std::vector<b2Body*> bodies;
		bodies.reserve(windows.size());

		for(auto& window: windows) {
			//auto size                      = getWindowSize(window.name);
			//auto positionRelativeToTopLeft = getWindowPosition(window.name);

			auto boxPosition =
			    screenToBoxCoords(window.position, window.size);

			std::cout
			    << "Name                    : " << window.name << "\n"
			    << "id                      : " << window.id << "\n"
			    << "RELATIVE TO TOP RIGHT X : " << window.position.x << "\n"
			    << "RELATIVE TO TOP RIGHT Y : " << window.position.y << "\n"
			    << "BOX2D WORLD COORDS X    : " << window.position.x << "\n"
			    << "BOX2D WORLD COORDS Y    : " << window.position.y << "\n"
			    << "Width                   : " << window.size.width << "\n"
			    << "Height                  : " << window.size.height << "\n"
			    << std::endl;

			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(boxPosition.x, boxPosition.y);

			b2Body* body = world.CreateBody(&bodyDef);

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(
			    window.size.width / 2.f,
			    window.size.height / 2.f);

			b2FixtureDef fixtureDef;
			fixtureDef.density  = 1.0f;
			fixtureDef.friction = 0.3f;

			fixtureDef.shape    = &dynamicBox;

			body->CreateFixture(&fixtureDef);

			bodies.push_back(body);
		}

		for(uint8_t i = 0; i < 255; ++i) {
			world.Step(timeStep, velocityIterations, positionIterations);

			for(uint8_t i = 0; i < bodies.size(); i++) {
				auto& body         = bodies[i];
				auto& window       = windows[i];

				b2Vec2 position    = body->GetPosition();
				float  angle       = body->GetAngle();
				auto   newPosition = boxToScreenCoords(
                                    {static_cast<uint16_t>(position.x),
                                     static_cast<uint16_t>(position.y)},
                                    window.size);

				if((window.position.x == newPosition.x &&
				    window.position.y == newPosition.y) ||
				   i < 10) {
					setWindowPosition(
					    window.id,
					    newPosition.x,
					    newPosition.y);
					window.position = newPosition;

					printf(
					    "%4.2f %4.2f %4.2f\n",
					    position.x,
					    position.y,
					    angle);
				}
			}
		}
	}

	return 0;
}
