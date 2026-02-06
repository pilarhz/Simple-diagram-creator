#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class InputBox {
public:
    InputBox();

    float GetNumber(sf::RenderWindow& window, const std::string& label);
private:
    sf::RectangleShape box;
    sf::Text labelText;
    sf::Text inputText;
};
