#pragma once

class DrawableObject {
public:
	virtual ~DrawableObject() = default;
	virtual void Draw(sf::RenderWindow& window) = 0;
};