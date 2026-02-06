#pragma once

const sf::Font MAIN_FONT("programFont.ttf");

const float CAMERA_SPEED = 15;
inline float gridSpacing = 30;
inline static float gridSize() { return gridSpacing * 500; };
inline static float gridStart() { return gridSize() * (-1); };
inline static float gridEnd() { return gridSize(); };