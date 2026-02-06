#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "../userInterface/ui.h"
#include "drawableObjects.h"
#include "../functions/functions.h"

// ============================= Scene =================================
class Scene {
public:
	void Draw(sf::RenderWindow& window);
	void Add(std::unique_ptr<DrawableObject> obj);
	void Remove(DrawableObject* obj);
private:
	std::vector<std::unique_ptr<DrawableObject>> objects;
};

// ============================= Grid =================================
class Grid : public DrawableObject {
public:
	Grid();
	void UpdateGrid();
private:
	std::vector<sf::Vertex> gridLines;
	std::vector<sf::RectangleShape> lineXY;
	std::vector<sf::Text> gridText;

	void SetGrid(float multipler);
	void Draw(sf::RenderWindow& window) override;
};
// ============================= Window =================================
class AppWindow {
public:
	AppWindow();
	void SetIcon(sf::Image icon);
	void StartApp();
	void RenderHandler();

	void SetGridForUpdate(Grid* g);
	void SetUiScene(Scene* scene);
	void SetUi(UserInterface* userI);

	void AddDrawable(std::unique_ptr<DrawableObject> obj);
	
	void MouseHoverEffect(const sf::Cursor& arrow, const sf::Cursor& hand);
	void MouseClicks();
	void CreateAndAdd(float y);

	// Adding function can be done better propably...
	void AddLinearFunction(LinearFunction* fx);
	void AddQuadraticFunction(QuadraticFunction* fx);
	void AddRationalFunction(RationalFunction* fx);
	void AddExponentialFunction(ExponentialFunction* fx);
	void AddLogarithmicFunction(LogarithmicFunction* fx);

	void UpdateGridAndFunctions();

	sf::RenderWindow* GetWindow() { return &window; }
private:
	sf::RenderWindow window;
	sf::View mainView;
	Scene scene;

	sf::View uiView;
	Scene* uiScene = nullptr;
	UserInterface* ui = nullptr;

	Grid* grid = nullptr;

	void DeleteFunction(size_t cardIndex);
	sf::Color GetNextColor();

	// Stores multiple Functions, this can be done better.
	// again propably
	std::vector<LinearFunction*> linear;
	std::vector<QuadraticFunction*> quadratic;
	std::vector<RationalFunction*> rational;
	std::vector<ExponentialFunction*> exponential;
	std::vector<LogarithmicFunction*> logarithmic;

	void EventHandler();
};