#pragma once

#include <memory>
#include <vector>
#include "../classes/drawableObjects.h"

class Scene;

class UserInterface : public DrawableObject {
public:
	void SetUserInterface(Scene* scene);
	void CreateMenu();
	void ChooseFunMenu(float y);
	void Draw(sf::RenderWindow& window) override;

	void AddCardHolder();
	void CreateCardHolder(sf::Color color, float y);
	void RepositionCardHolders();                     

	// CardHolders
	std::vector<sf::RectangleShape> cardHolder;
	std::vector<sf::Text> cardTextHolder;
	std::vector<sf::Text> deleteCross;                

	// Function in cards
	std::vector<int> functionType;                   
	std::vector<size_t> functionIndex;

	std::vector<sf::RectangleShape> chooseMR;
	std::vector<sf::Text> chooseMT;

private:
	Scene* uiScene = nullptr;
	std::vector<sf::RectangleShape> menuHolder;
	std::vector<sf::Text> textControls;
};