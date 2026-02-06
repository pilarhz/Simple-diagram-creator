#include "inputBox.h" // Header file

#include "../worldVariables/worldVariables.h"

InputBox::InputBox()
    : labelText(MAIN_FONT),
    inputText(MAIN_FONT)
{
    box.setSize({ 200.f, 100.f });
    box.setFillColor(sf::Color(15, 16, 19));
    box.setOutlineThickness(3);
    box.setOutlineColor(sf::Color(118, 229, 252));

    labelText.setCharacterSize(20);
    labelText.setFillColor(sf::Color::White);

    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::White);
}

float InputBox::GetNumber(sf::RenderWindow& window, const std::string& label) {

    std::string input = "";

    sf::Vector2u size = window.getSize();

    float currSize{};

    box.setPosition({ size.x / 2 - 100.f, size.y / 2 - 50.f });

    labelText.setString(label);
    labelText.setPosition({ size.x / 2 - 40.f, size.y / 2 - 40.f });

    inputText.setPosition({ size.x / 2 - currSize, size.y / 2.f });

    while (1) {
        inputText.setPosition({ size.x / 2 - currSize, size.y / 2.f });
        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
                return 0; 
            }

            if (auto textEntered = event->getIf<sf::Event::TextEntered>()) {
                if (textEntered->unicode >= '0' && textEntered->unicode <= '9') {
                    input += static_cast<char>(textEntered->unicode);
                }
            }

            if (auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Backspace && !input.empty()) {
                    input.pop_back();
                }

                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    if (input.empty())
                        return 1;
                    return std::stof(input);
                }
            }
        }
        currSize = static_cast<float>(input.length() * 5.5);

        inputText.setString(input);

        window.draw(box);
        window.draw(labelText);
        window.draw(inputText);
        window.display();
    }
}