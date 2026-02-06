#include "../classes/classes.h"
#include "../worldVariables/worldVariables.h"

static sf::Text CreateText(sf::Text& text, std::string str, sf::Vector2f pos) {
    text.setString(str);
    text.setPosition(pos);
    return text;
}

static sf::RectangleShape CreateRect(sf::Vector2f size, sf::Vector2f pos, sf::Color color) {
    sf::RectangleShape rect;
    rect.setSize(size);
    rect.setPosition(pos);
    rect.setFillColor(color);
    return rect;
}

void UserInterface::SetUserInterface(Scene* scene) {
    uiScene = scene;
}

void UserInterface::CreateMenu() {
    sf::RectangleShape menu = CreateRect({ 350.f, 2000.f }, { 0.f,0.f }, sf::Color(15, 16, 19));
    menuHolder.push_back(menu);

    sf::RectangleShape menuL = CreateRect({ 1.f, 2000.f }, { 350.f, 0.f }, sf::Color(100, 100, 100));
    menuHolder.push_back(menuL);

    sf::Text text(MAIN_FONT);
    text.setCharacterSize(13);
    text.setFillColor(sf::Color::White);
    textControls.push_back(CreateText(text, "Scroll - oddalanie/przyblizanie", { 355.f, 5.f }));
    textControls.push_back(CreateText(text, "WSAD - Ruszanie po siatce", { 355.f, 25.f }));
    textControls.push_back(CreateText(text, "SPACE - Wysrodkuj", { 355.f, 45.f }));
    textControls.push_back(CreateText(text, "R - Reset zooma", { 355.f, 65.f }));
    textControls.push_back(CreateText(text, "ESC - Wyjscie", { 355.f, 85.f }));
}

void UserInterface::Draw(sf::RenderWindow& window) {
    for (auto& i : menuHolder) { window.draw(i); }
    for (auto& i : textControls) { window.draw(i); }
    for (auto& i : cardHolder) { window.draw(i); }
    for (auto& i : cardTextHolder) { window.draw(i); }
    for (auto& i : deleteCross) { window.draw(i); }
    for (auto& i : chooseMR) { window.draw(i); }
    for (auto& i : chooseMT) { window.draw(i); }
}

void UserInterface::CreateCardHolder(sf::Color color, float y) {
    sf::Text text(MAIN_FONT);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    cardHolder.push_back(CreateRect({ 350.f, 50.f }, { 0.f, y }, color)); // Card "outline"
    cardHolder.push_back(CreateRect({ 300.f, 40.f }, { 45.f, y + 5 }, sf::Color(15, 16, 19))); // Card

    text.setString("Dodaj f(x)"); // Text in card
    text.setPosition({ 60.f, y + 12 });
    cardTextHolder.push_back(text);

    // Delete function button
    sf::Text cross(MAIN_FONT);
    cross.setString("×");
    cross.setCharacterSize(45);
    cross.setFillColor(sf::Color(255, 80, 80));
    cross.setPosition({ 313.f, y - 3 });
    deleteCross.push_back(cross);
}

void UserInterface::RepositionCardHolders() {
    for (size_t i = 0; i < cardTextHolder.size(); ++i) {
        float newY = i * 50.f;
        cardHolder[i * 2].setPosition({ 0.f, newY }); // Card "outline"
        cardHolder[i * 2 + 1].setPosition({ 45.f, newY + 5 }); // Card
        cardTextHolder[i].setPosition({ 60.f, newY + 12 }); // Text
        deleteCross[i].setPosition({ 313.f, newY - 3 }); // Cross
    }
}

sf::Color cc(206, 210, 209);
void UserInterface::AddCardHolder() {
    switch (cardHolder.size()) {
        case 0: CreateCardHolder(cc, 0.f); break;
        case 2: CreateCardHolder(cc, 50.f); break;
        case 4: CreateCardHolder(cc, 100.f); break;
        case 6: CreateCardHolder(cc, 150.f); break;
        case 8: CreateCardHolder(cc, 200.f); break;
        case 10: CreateCardHolder(cc, 250.f); break;
        case 12: CreateCardHolder(cc, 300.f); break;
        case 14: CreateCardHolder(cc, 350.f); break;
        case 16: CreateCardHolder(cc, 400.f); break;
        case 18: CreateCardHolder(cc, 450.f); break;
        case 20: CreateCardHolder(cc, 500.f); break;
        case 22: CreateCardHolder(cc, 550.f); break;
        case 24: CreateCardHolder(cc, 600.f); break;
        case 26: CreateCardHolder(cc, 650.f); break;
        case 28: CreateCardHolder(cc, 700.f); break;
        case 30: CreateCardHolder(cc, 3000.f); break;
    }
}

void UserInterface::ChooseFunMenu(float y) {
    chooseMR.push_back(CreateRect({ 180.f, 260.f }, { 350.f, y }, sf::Color(22, 38, 46)));

    sf::Text text(MAIN_FONT); 
    text.setCharacterSize(22);
    text.setFillColor(sf::Color::White);

    float sx = 160.f, sy = 40.f, x = 360.f, tx = 370.f;
    float s = 10; // spacing

    chooseMR.push_back(CreateRect({ sx, sy }, { x, y + s }, sf::Color(15, 16, 19)));
    chooseMT.push_back(CreateText(text, "Liniowa", { tx + 30, y + s + 5}));

    chooseMR.push_back(CreateRect({ sx, sy }, { x, y + (s * 2) + (sy * 1) }, sf::Color(15, 16, 19)));
    chooseMT.push_back(CreateText(text, "Kwadratowa", { tx + 11, y + (s * 2) + (sy * 1) + 5 }));

    chooseMR.push_back(CreateRect({ sx, sy }, { x, y + (s * 3) + (sy * 2) }, sf::Color(15, 16, 19)));
    chooseMT.push_back(CreateText(text, "Wymierna", { tx + 18, y + (s * 3) + (sy * 2) + 5 }));

    chooseMR.push_back(CreateRect({ sx, sy }, { x, y + (s * 4) + (sy * 3) }, sf::Color(15, 16, 19)));
    chooseMT.push_back(CreateText(text, "Wykladnicza", { tx + 7, y + (s * 4) + (sy * 3) + 5 }));

    chooseMR.push_back(CreateRect({ sx, sy }, { x, y + (s * 5) + (sy * 4) }, sf::Color(15, 16, 19)));
    chooseMT.push_back(CreateText(text, "Logarytmiczna", { tx - 2, y + (s * 5) + (sy * 4) + 5 }));
}