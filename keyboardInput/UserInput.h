#pragma once

#include <SFML/Graphics.hpp>

bool MoveCamera(sf::Vector2f& move);
bool CenterCamera();
bool CloseWindow();
bool ZoomReset();
void Scroll(const sf::Event::MouseWheelScrolled& wheel);
float InputNum(const std::string& label = "Podaj liczbe:");