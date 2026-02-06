#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random> // GetNextColor

#include "classes.h"
#include "../worldVariables/worldVariables.h"
#include "../keyboardInput/UserInput.h"

#include "../functions/functions.h"

float num = 1; float funNum = 1;
sf::RectangleShape card1, card2, card3, card4, card5, card6, card7, card8, card9, card10, card11, card12, card13, card14, card15;
sf::RectangleShape f1, f2, f3, f4, f5;
sf::RectangleShape* hover[20] = { &card1, &card2, &card3, &card4, &card5, 
								&card6, &card7, &card8, &card9, &card10,
								&card11, &card12, &card13, &card14, &card15,
								&f1, &f2, &f3, &f4, &f5 };

// ============================= Scene class definition =================================
void Scene::Draw(sf::RenderWindow& window) {
	for (auto& obj : objects) {
		obj->Draw(window);
	}
}

void Scene::Add(std::unique_ptr<DrawableObject> obj) {
	objects.push_back(std::move(obj));
}

void Scene::Remove(DrawableObject* obj) {
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		if (it->get() == obj) {
			objects.erase(it);
			break;
		}
	}
}

// ============================= Window class definition =================================
AppWindow::AppWindow() : 
	window(
	sf::VideoMode({ 1400, 800}), 
	"Prosty kreator wykresów", 
	sf::Style::Default, 
	sf::State::Windowed
), mainView(
	sf::View(
		sf::FloatRect(
			{ 0.f, 0.f }, 
			{1400.f, 800.f}
		)
	)
), uiView(
	sf::View(
		sf::FloatRect(
			{ 0.f, 0.f },
			{ 1400.f, 800.f }
		)
	)
) {}

void AppWindow::SetIcon(sf::Image icon) {
	window.setIcon(icon);
}

void AppWindow::SetUi(UserInterface* userI) {
	ui = userI;
}

void AppWindow::CreateAndAdd(float y) {
	ui->ChooseFunMenu(y);
	f1 = ui->chooseMR[1];
	f2 = ui->chooseMR[2];
	f3 = ui->chooseMR[3];
	f4 = ui->chooseMR[4];
	f5 = ui->chooseMR[5];
}

sf::Color AppWindow::GetNextColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> high(200, 255);  // Bardzo jasny/nasycony
    std::uniform_int_distribution<> mid(100, 180);   // Œredni (dla przejœæ)
    std::uniform_int_distribution<> low(0, 50);      // Ciemny (dla kontrastu)
    std::uniform_int_distribution<> colorWheel(0, 6); // 7 g³ównych typów kolorów

    sf::Color newColor;
    int choice = colorWheel(gen);

    switch (choice) {
        case 0: // Czerwony (Jasny)
            newColor = sf::Color(high(gen), low(gen), low(gen)); break;
        case 1: // Pomarañczowy
            newColor = sf::Color(high(gen), mid(gen), low(gen)); break;
        case 2: // ¯ó³ty
            newColor = sf::Color(high(gen), high(gen), low(gen)); break;
        case 3: // Zielony (Limonkowy/Jasny)
            newColor = sf::Color(low(gen), high(gen), low(gen)); break;
        case 4: // Niebieski (B³êkit królewski)
            newColor = sf::Color(low(gen), mid(gen), high(gen)); break;
        case 5: // Ró¿owy (Hot Pink)
            newColor = sf::Color(high(gen), low(gen), mid(gen)); break;
        case 6: // Fioletowy
            newColor = sf::Color(mid(gen), low(gen), high(gen)); break;
    }
    newColor.a = 255;
    return newColor;
}

void AppWindow::MouseClicks() {
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {}

		mousePixelPos = sf::Mouse::getPosition(window);
		mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

		for (size_t i = 0; i < ui->deleteCross.size(); ++i) {
			if (ui->deleteCross[i].getGlobalBounds().contains(mouseWorldPos)) {
				DeleteFunction(i);
				return;
			}
		}
		if (f1.getGlobalBounds().contains(mouseWorldPos)) {
			sf::Color randomColor = GetNextColor();
			auto fun = std::make_unique<LinearFunction>(randomColor, funNum);
			AddLinearFunction(fun.get());
			size_t cardIndex = ui->cardTextHolder.size() - 2;
			ui->cardTextHolder[cardIndex].setString(fun->GetString());
			ui->cardHolder[cardIndex * 2].setFillColor(randomColor);
			AddDrawable(std::move(fun));
			ui->functionType.push_back(0);
			ui->functionIndex.push_back(linear.size() - 1);
			ui->chooseMR.clear(); ui->chooseMT.clear();
		}
		else if (f2.getGlobalBounds().contains(mouseWorldPos)) {
			sf::Color randomColor = GetNextColor();
			auto fun = std::make_unique<QuadraticFunction>(randomColor, funNum);
			AddQuadraticFunction(fun.get());
			size_t cardIndex = ui->cardTextHolder.size() - 2;
			ui->cardTextHolder[cardIndex].setString(fun->GetString());
			ui->cardHolder[cardIndex * 2].setFillColor(randomColor);
			AddDrawable(std::move(fun));
			ui->functionType.push_back(1);
			ui->functionIndex.push_back(quadratic.size() - 1);
			ui->chooseMR.clear(); ui->chooseMT.clear();
		}
		else if (f3.getGlobalBounds().contains(mouseWorldPos)) {
			sf::Color randomColor = GetNextColor();
			auto fun = std::make_unique<RationalFunction>(randomColor, funNum);
			AddRationalFunction(fun.get());
			size_t cardIndex = ui->cardTextHolder.size() - 2;
			ui->cardTextHolder[cardIndex].setString(fun->GetString());
			ui->cardHolder[cardIndex * 2].setFillColor(randomColor);
			AddDrawable(std::move(fun));
			ui->functionType.push_back(2);
			ui->functionIndex.push_back(rational.size() - 1);
			ui->chooseMR.clear(); ui->chooseMT.clear();
		}
		else if (f4.getGlobalBounds().contains(mouseWorldPos)) {
			sf::Color randomColor = GetNextColor();
			auto fun = std::make_unique<ExponentialFunction>(randomColor, funNum);
			AddExponentialFunction(fun.get());
			size_t cardIndex = ui->cardTextHolder.size() - 2;
			ui->cardTextHolder[cardIndex].setString(fun->GetString());
			ui->cardHolder[cardIndex * 2].setFillColor(randomColor);
			AddDrawable(std::move(fun));
			ui->functionType.push_back(3);
			ui->functionIndex.push_back(exponential.size() - 1);
			ui->chooseMR.clear(); ui->chooseMT.clear();
		}
		else if (f5.getGlobalBounds().contains(mouseWorldPos)) {
			sf::Color randomColor = GetNextColor();
			auto fun = std::make_unique<LogarithmicFunction>(randomColor, funNum);
			AddLogarithmicFunction(fun.get());
			size_t cardIndex = ui->cardTextHolder.size() - 2;
			ui->cardTextHolder[cardIndex].setString(fun->GetString());
			ui->cardHolder[cardIndex * 2].setFillColor(randomColor);
			AddDrawable(std::move(fun));
			ui->functionType.push_back(4);
			ui->functionIndex.push_back(logarithmic.size() - 1);
			ui->chooseMR.clear(); ui->chooseMT.clear();
		}

		if (card1.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 2) {
			CreateAndAdd(0);
			ui->AddCardHolder();
			card2 = ui->cardHolder[3];
		}
		if (card2.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 4) {
			CreateAndAdd(50);
			ui->AddCardHolder();
			card3 = ui->cardHolder[5];
		}
		if (card3.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 6) {
			CreateAndAdd(100);
			ui->AddCardHolder();
			card4 = ui->cardHolder[7];
		}
		if (card4.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 8) {
			CreateAndAdd(150);
			ui->AddCardHolder();
			card5 = ui->cardHolder[9];
		}
		if (card5.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 10) {
			CreateAndAdd(200);
			ui->AddCardHolder();
			card6 = ui->cardHolder[11];
		}
		if (card6.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 12) {
			CreateAndAdd(250);
			ui->AddCardHolder();
			card7 = ui->cardHolder[13];
		}
		if (card7.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 14) {
			CreateAndAdd(300);
			ui->AddCardHolder();
			card8 = ui->cardHolder[15];
		}
		if (card8.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 16) {
			CreateAndAdd(350);
			ui->AddCardHolder();
			card9 = ui->cardHolder[17];
		}
		if (card9.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 18) {
			CreateAndAdd(400);
			ui->AddCardHolder();
			card10 = ui->cardHolder[19];
		}
		if (card10.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 20) {
			CreateAndAdd(450);
			ui->AddCardHolder();
			card11 = ui->cardHolder[21];
		}
		if (card11.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 22) {
			CreateAndAdd(500);
			ui->AddCardHolder();
			card12 = ui->cardHolder[23];
		}
		if (card12.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 24) {
			CreateAndAdd(550);
			ui->AddCardHolder();
			card13 = ui->cardHolder[25];
		}
		if (card13.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 26) {
			CreateAndAdd(600);
			ui->AddCardHolder();
			card14 = ui->cardHolder[27];
		}
		if (card14.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 28) {
			CreateAndAdd(650);
			ui->AddCardHolder();
			card15 = ui->cardHolder[29];
		}
		if (card15.getGlobalBounds().contains(mouseWorldPos) && ui->cardHolder.size() == 30) {
			CreateAndAdd(700);
			ui->AddCardHolder();
		}
	}
}

void AppWindow::StartApp() { // ################################# WINDOW LOOP ######################
	const sf::Cursor arrowCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
	const sf::Cursor handCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
	
	ui->AddCardHolder(); card1 = ui->cardHolder[1]; // First card

	mainView.move({ -875.f, -400.f }); // Center view on 0,0 XY

	window.setFramerateLimit(100); 
	// Frame limit is set to static number so everybody have the same camera speed

	sf::Vector2f cameraVector;

	while (window.isOpen()) {

		EventHandler();

		if (CloseWindow()) { window.close(); } // ESC
		if (MoveCamera(cameraVector)) { mainView.move(cameraVector); cameraVector = {}; } // WSAD
		if (CenterCamera()) { mainView.setCenter({ -175.f, 0.f }); } // SPACE
		if (ZoomReset()) { num = 1; funNum = 1; gridSpacing = 30; UpdateGridAndFunctions(); } // R

		MouseHoverEffect(arrowCursor, handCursor);
		MouseClicks();

		RenderHandler();
	}
} // ################################### WINDOW LOOP ##########################

void AppWindow::MouseHoverEffect(const sf::Cursor& arrow, const sf::Cursor& hand) {
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

	bool isHovering = false;

	for (size_t i = 0; i < 20; ++i) {
		if (hover[i]->getGlobalBounds().contains(mouseWorldPos)) {
			isHovering = true;
			break;
		}
	}

	if (isHovering) { window.setMouseCursor(hand); }
	else { window.setMouseCursor(arrow); }
}

void AppWindow::RenderHandler() {
	window.clear();

	window.setView(mainView);
	scene.Draw(window);

	if (uiScene) {
		window.setView(uiView);
		uiScene->Draw(window);
		ui->Draw(window);
	}

	window.display();
}

void AppWindow::SetGridForUpdate(Grid* g) {
	grid = g;
}

void AppWindow::AddLinearFunction(LinearFunction* fx) {
	linear.push_back(fx);
}

void AppWindow::AddQuadraticFunction(QuadraticFunction* fx) {
	quadratic.push_back(fx);
}

void AppWindow::AddRationalFunction(RationalFunction* fx) {
	rational.push_back(fx);
}

void AppWindow::AddExponentialFunction(ExponentialFunction* fx) {
	exponential.push_back(fx);
}

void AppWindow::AddLogarithmicFunction(LogarithmicFunction* fx) {
	logarithmic.push_back(fx);
}

void AppWindow::SetUiScene(Scene* scene) {
	uiScene = scene;
}

void AppWindow::AddDrawable(std::unique_ptr<DrawableObject> obj) {
	scene.Add(std::move(obj));
}

void AppWindow::UpdateGridAndFunctions() {
	grid->UpdateGrid();
	for (auto& i : linear) { i->UpdateLinear(funNum); }
	for (auto& i : quadratic) { i->UpdateQuadratic(funNum); }
	for (auto& i : rational) { i->UpdateRational(funNum); }
	for (auto& i : exponential) { i->UpdateExponential(funNum); }
	for (auto& i : logarithmic) { i->UpdateLogarithmic(funNum); }
}

void AppWindow::EventHandler() {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (const auto* resized = event->getIf<sf::Event::Resized>()) {
			sf::Vector2f newSize(resized->size);
			sf::Vector2f halfSize = newSize * 0.5f;
			sf::Vector2f center = mainView.getCenter();
			mainView = sf::View{ sf::FloatRect(center - halfSize, newSize) };

			uiView.setSize(newSize);
			uiView.setCenter(newSize * 0.5f);
		}
		if (const auto* wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
			Scroll(*wheel);
			UpdateGridAndFunctions();
		}
	}
}

void AppWindow::DeleteFunction(size_t cardIndex) {
	int type = ui->functionType[cardIndex];
	size_t idx = ui->functionIndex[cardIndex];

	DrawableObject* objToRemove = nullptr;

	switch (type) {
	case 0: // Linear
		if (idx < linear.size()) {
			objToRemove = linear[idx];
			linear.erase(linear.begin() + idx);
		}
		break;
	case 1: // Quadratic
		if (idx < quadratic.size()) {
			objToRemove = quadratic[idx];
			quadratic.erase(quadratic.begin() + idx);
		}
		break;
	case 2: // Rational
		if (idx < rational.size()) {
			objToRemove = rational[idx];
			rational.erase(rational.begin() + idx);
		}
		break;
	case 3: // Exponential
		if (idx < exponential.size()) {
			objToRemove = exponential[idx];
			exponential.erase(exponential.begin() + idx);
		}
		break;
	case 4: // Logarithmic
		if (idx < logarithmic.size()) {
			objToRemove = logarithmic[idx];
			logarithmic.erase(logarithmic.begin() + idx);
		}
		break;
	}

	if (objToRemove) {
		scene.Remove(objToRemove);
	}

	ui->cardHolder.erase(ui->cardHolder.begin() + cardIndex * 2, ui->cardHolder.begin() + cardIndex * 2 + 2);
	ui->cardTextHolder.erase(ui->cardTextHolder.begin() + cardIndex);
	ui->deleteCross.erase(ui->deleteCross.begin() + cardIndex);
	ui->functionType.erase(ui->functionType.begin() + cardIndex);
	ui->functionIndex.erase(ui->functionIndex.begin() + cardIndex);

	for (size_t i = 0; i < ui->functionType.size(); ++i) {
		if (ui->functionType[i] == type && ui->functionIndex[i] > idx) {
			ui->functionIndex[i]--;
		}
	}

	ui->RepositionCardHolders();
}

// ============================= Grid class definition =================================
Grid::Grid() {
	SetGrid(1);
}

void Grid::SetGrid(float multipler) {
	sf::Color white(100, 100, 100);
	sf::Color gray(25, 25, 25);

	int count = 5;
	for (float i = gridStart(); i <= gridEnd(); i += gridSpacing) {
		if (i == 0 || count == 5) { count = 1;  continue; }
		gridLines.push_back(sf::Vertex{ sf::Vector2f(i, gridStart()), gray });
		gridLines.push_back(sf::Vertex{ sf::Vector2f(i, gridEnd()), gray });

		gridLines.push_back(sf::Vertex{ sf::Vector2f(gridStart(), i), gray });
		gridLines.push_back(sf::Vertex{ sf::Vector2f(gridEnd(), i), gray });
		count++;
	}
	for (float i = gridStart(); i <= gridEnd(); i += gridSpacing * 5) {
		if (i == 0) { continue; }
		gridLines.push_back(sf::Vertex{ sf::Vector2f(i, gridStart()), white });
		gridLines.push_back(sf::Vertex{ sf::Vector2f(i, gridEnd()), white });

		gridLines.push_back(sf::Vertex{ sf::Vector2f(gridStart(), i), white });
		gridLines.push_back(sf::Vertex{ sf::Vector2f(gridEnd(), i), white });
	}

	lineXY.resize(2);

	lineXY[0] = sf::RectangleShape({ gridSize() * 2, 3.f });
	lineXY[0].setFillColor(sf::Color::White);
	lineXY[0].setPosition({ gridStart(), -1 });

	lineXY[1] = sf::RectangleShape({ 3.f, gridSize() * 2 });
	lineXY[1].setFillColor(sf::Color::White);
	lineXY[1].setPosition({ -1, gridStart() });

	for (float i = gridStart(); i <= gridEnd(); i += gridSpacing * 5) {
		sf::Text text(MAIN_FONT);

		std::ostringstream number;
		number << std::setprecision(100) << ((i / (gridSpacing * 5)) * multipler);

		text.setString(number.str());
		text.setCharacterSize(18);
		text.setFillColor(sf::Color::White);
		text.setPosition({ i + 3, 0.f });

		gridText.push_back(text);
		if (i == 0) { continue; }
		text.setPosition({ 4.f, -i });
		gridText.push_back(text);
	}
}

void Grid::UpdateGrid() {
	gridLines.clear();
	lineXY.clear();
	gridText.clear();

	if (gridSpacing > 40) { gridSpacing = 20; num *= 0.5; funNum *= 2; }
	else if (gridSpacing < 20) { gridSpacing = 40; num *= 2; funNum *= 0.5f; }
	SetGrid(num);
}

void Grid::Draw(sf::RenderWindow& window) {
	window.draw(gridLines.data(), gridLines.size(), sf::PrimitiveType::Lines);
	window.draw(lineXY[0]);
	window.draw(lineXY[1]);
	for (int i = 0; i < gridText.size(); i++) {
		window.draw(gridText[i]);
	}
}