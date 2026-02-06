#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../classes/drawableObjects.h"

// NOTE:
// Classes seems fine, 
// now the question is how to draw them on screen

// Liniowa, f(x) = ax + b
class LinearFunction : public DrawableObject { 
public:
	LinearFunction(sf::Color col, float g);
	void UpdateLinear(float g);
	std::string GetString();
private:
	void Draw(sf::RenderWindow& window) override;
	float a, b;
	sf::Color color;
	std::vector<sf::Vertex> lines;
};

// Kwadratowa, f(x) = ax^2 + bx + c
class QuadraticFunction : public DrawableObject {
public:
	QuadraticFunction(sf::Color col, float g);
	void UpdateQuadratic(float g);
	std::string GetString();
private:
	void Draw(sf::RenderWindow& window) override;
	float a, b, c;
	sf::Color color;
	std::vector<sf::Vertex> points;
};

// Wymierna, f(x) = (ax + b) / (cx + b)
class RationalFunction : public DrawableObject {
public:
	RationalFunction(sf::Color col, float g);
	void UpdateRational(float g);
	std::string GetString();
private:
	void Draw(sf::RenderWindow& window) override;
	float a, b, c;
	sf::Color color;
	std::vector<sf::Vertex> points;
};

// Wyk³adnicza, f(x) = a^x
class ExponentialFunction : public DrawableObject {
public:
	ExponentialFunction(sf::Color col, float g);
	void UpdateExponential(float g);
	std::string GetString();
private:
	void Draw(sf::RenderWindow& window) override;
	float a;
	sf::Color color;
	std::vector<sf::Vertex> points;
};

// Logarytmiczna, f(x) = log[(a) x] 
class LogarithmicFunction : public DrawableObject {
public:
	LogarithmicFunction(sf::Color col, float g);
	void UpdateLogarithmic(float g);
	std::string GetString();
private:
	void Draw(sf::RenderWindow& window) override;
	float a;
	sf::Color color;
	std::vector<sf::Vertex> points;
};