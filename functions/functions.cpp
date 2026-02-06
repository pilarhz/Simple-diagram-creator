#include <math.h>
#include <sstream>

#include "functions.h"
#include "../worldVariables/worldVariables.h"
#include "../keyboardInput/UserInput.h"

// ================================================= Linear ====================
LinearFunction::LinearFunction(sf::Color col, float g) {
	color = col;
	a = InputNum("Podaj A");
	b = InputNum("Podaj B");

	float fix = -gridSpacing * 5 * g; // Scale function
	float x = gridStart();
	float y = -x * a + b * fix;

	lines.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
	x = gridEnd(); y = -x * a + b * fix;
	lines.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
}

void LinearFunction::UpdateLinear(float g) {
	float fix = -gridSpacing * 5 * g; // Scale function
	float x{}, y{};
	for (int i = 0; i < lines.size(); i += 2) {
		x = gridStart();
		y = -x * a + b * fix;
		y = round(y);
		lines[i].position = { x, y };
		x = gridEnd();
		y = -x * a + b * fix;
		lines[i + 1].position = { x, y };
	}
}

void LinearFunction::Draw(sf::RenderWindow& window) {
	window.draw(lines.data(), lines.size(), sf::PrimitiveType::Lines);
}

std::string LinearFunction::GetString() {
	std::ostringstream ss;
	ss << "f(x) = " << a << "x + " << b;
	return ss.str();
}

// ================================================= Quadratic ====================
QuadraticFunction::QuadraticFunction(sf::Color col, float g) {
	color = col;
	a = InputNum("Podaj A");
	b = InputNum("Podaj B");
	c = InputNum("Podaj C");
	float y{};
	float aFix = a / (gridSpacing * 5 * g); // Scale function
	float cFix = c * gridSpacing * 5 * g; // Scale function
	for (float x = gridStart(); x <= gridEnd(); x++) {
		y = -((pow(x, 2) * aFix) + (b * x) + cFix);
		if (y > gridEnd() || y < gridStart()) { continue; }
		else {
			points.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
		}
	}
}

void QuadraticFunction::UpdateQuadratic(float g) {
	float y{};
	float aFix = a / (gridSpacing * 5 * g);
	float cFix = c * gridSpacing * 5 * g;
	points.clear();
	for (float x = gridStart(); x <= gridEnd(); x++) {
		y = -((pow(x, 2) * aFix) + (b * x) + cFix);
		if (y > gridEnd() || y < gridStart()) { continue; }
		else {
			points.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
		}
	}
}

void QuadraticFunction::Draw(sf::RenderWindow& window) {
	window.draw(points.data(), points.size(), sf::PrimitiveType::LineStrip);
}

std::string QuadraticFunction::GetString() {
	std::ostringstream ss;
	ss << "f(x) = " << a << "x^2 + " << b << "x + " << c;
	return ss.str();
}

// ================================================= Rational ==================================
#include <iostream>
RationalFunction::RationalFunction(sf::Color col, float g) {
	color = col;
	a = InputNum("Podaj A");
	b = InputNum("Podaj B");
	c = InputNum("Podaj C");
	float prevY{};
	float y{};
	float bFix = b * gridSpacing * 5 * g; // Scale function
	for (float x = gridStart(); x <= gridEnd(); x++) {
		y = (gridSpacing * 5 * g) * -(((a * x) + bFix) / ((c * x) + bFix));
		if (y > gridEnd() || y < gridStart()) { continue; }
		else {
			points.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
		}
		prevY = y;
	}
}

void RationalFunction::UpdateRational(float g) {
	float y{}, bFix = b * gridSpacing * 5 * g;
	points.clear();
	for (float x = gridStart(); x <= gridEnd(); x++) {
		y = (gridSpacing * 5 * g) * -(((a * x) + bFix) / ((c * x) + bFix));
		if (y > gridEnd() || y < gridStart()) { continue; }
		else {
			points.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
		}
	}
}

void RationalFunction::Draw(sf::RenderWindow& window) {
	window.draw(points.data(), points.size(), sf::PrimitiveType::LineStrip);
}

std::string RationalFunction::GetString() {
	std::ostringstream ss;
	ss << "f(x) = (" << a << "x + " << b << ") / (" << c << "x + " << b << ")";
	return ss.str();
}

// ============================================== EponentialFunction ======================
ExponentialFunction::ExponentialFunction(sf::Color col, float g) {
	color = col;
	a = InputNum("Podaj A");
	float y{};
	float fix = gridSpacing * 5 * g; // Scale function
	for (float x = gridStart(); x <= gridEnd(); x++) {
		y = fix * -(pow(a, (x / fix)));
		if (y > gridEnd() || y < gridStart()) { continue; }
		else {
			points.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
		}
	}
}

void ExponentialFunction::UpdateExponential(float g) {
	float y{};
	float fix = gridSpacing * 5 * g;
	points.clear();
	for (float x = gridStart(); x <= gridEnd(); x++) {
		y = fix * -(pow(a, (x / fix)));
		if (y > gridEnd() || y < gridStart()) { continue; }
		else {
			points.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
		}
	}
}

void ExponentialFunction::Draw(sf::RenderWindow& window) {
	window.draw(points.data(), points.size(), sf::PrimitiveType::LineStrip);
}

std::string ExponentialFunction::GetString() {
	std::ostringstream ss;
	ss << "f(x) = " << a << "^x";
	return ss.str();
}

// ============================================= Logarithmic ==============================
LogarithmicFunction::LogarithmicFunction(sf::Color col, float g) {
	color = col;
	a = InputNum("Podaj A");
	float y{};
	float fix = gridSpacing * 5 * g; // Scale function
	for (float x = gridStart(); x < gridEnd(); x++) {

		y = fix * -((std::log(x / fix)) / (std::log(a)));

		if (y > gridEnd() || y < gridStart()) { continue; }
		else {
			points.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
		}
	}
}

void LogarithmicFunction::UpdateLogarithmic(float g) {
	float y{};
	float fix = gridSpacing * 5 * g;
	points.clear();
	for (float x = gridStart(); x < gridEnd(); x++) {

		y = fix * -((std::log(x / fix)) / (std::log(a)));

		if (y > gridEnd() || y < gridStart()) { continue; }
		else {
			points.push_back(sf::Vertex{ sf::Vector2f(x, y), color });
		}
	}
}

void LogarithmicFunction::Draw(sf::RenderWindow& window) {
	window.draw(points.data(), points.size(), sf::PrimitiveType::LineStrip);
}

std::string LogarithmicFunction::GetString() {
	std::ostringstream ss;
	ss << "f(x) = log_" << a << "(x)";
	return ss.str();
}