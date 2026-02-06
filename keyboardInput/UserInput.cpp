#include "UserInput.h" // header

#include <string>

#include "../classes/classes.h"
#include "../worldVariables/worldVariables.h"
#include "../inputbox/inputBox.h"

bool MoveCamera(sf::Vector2f& move) {
	bool pressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { move.x += -CAMERA_SPEED; pressed = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { move.x += CAMERA_SPEED; pressed = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { move.y += -CAMERA_SPEED; pressed = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { move.y += CAMERA_SPEED; pressed = true; }
	return pressed;
}

bool CenterCamera() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) { return true; }
	else { return false; }
}

bool CloseWindow() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) { return true; }
	else { return false; }
}

bool ZoomReset() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) { return true; }
	else { return false; }
}

void Scroll(const sf::Event::MouseWheelScrolled& wheel) {
	if (wheel.wheel == sf::Mouse::Wheel::Vertical) {
		if ((1.f + wheel.delta * 0.1f) > 1) {
			gridSpacing = gridSpacing - 1;
		}
		else if ((1.f + wheel.delta * 0.1f) < 1) {
			gridSpacing = gridSpacing + 1;
		}
	}
}

extern AppWindow* globalAppWindow;
float InputNum(const std::string& label) {
	InputBox box;
	return box.GetNumber(*globalAppWindow->GetWindow(), label);
}