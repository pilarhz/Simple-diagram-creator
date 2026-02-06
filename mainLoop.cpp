#include "classes/classes.h"

AppWindow* globalAppWindow;

int main() {
	AppWindow window;
	globalAppWindow = &window;

	sf::Image icon;
	if (!icon.loadFromFile("windowIcon.png")) { return -1; }
	window.SetIcon(icon);

	UserInterface userInterface;
	Scene uiScene;
	userInterface.SetUserInterface(&uiScene);
	window.SetUiScene(&uiScene);

	userInterface.CreateMenu();
	window.SetUi(&userInterface);

	auto grid = std::make_unique<Grid>();
	window.SetGridForUpdate(grid.get());
	window.AddDrawable(std::move(grid));

	window.StartApp(); // Window main loop

	return 0;
}