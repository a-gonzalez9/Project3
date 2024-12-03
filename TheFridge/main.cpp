#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <filesystem>

using namespace std;

int main() {
    cout << "Current working directory: " << filesystem::current_path() << endl;

    namespace fs = std::filesystem;
    if (fs::exists("../Ubuntu/Ubuntu-Regular.ttf")) {
        std::cout << "Font file found!" << std::endl;
    } else {
        std::cout << "Font file not found." << std::endl;
        return -1;
    }

    // Create window that fills the entire screen
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Recipe App", sf::Style::Fullscreen);

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("../Ubuntu/Ubuntu-Regular.ttf")) {
        cerr << "Error: Could not load Ubuntu/Ubuntu-Regular.ttf" << endl;
        return -1;
    }

    int currentPage = 1;
    vector<string> preferences;
    vector<string> avoidances;
    vector<string> priorities;

    // Create "DONE" button
    sf::Text doneButton("DONE", font, 30);
    doneButton.setFillColor(sf::Color::White);
    doneButton.setStyle(sf::Text::Bold);
    doneButton.setPosition((window.getSize().x - doneButton.getGlobalBounds().width) / 2.0f, window.getSize().y - 100.0f);

    // Elements for page 1
    sf::Texture fridgeTexture;
    if (!fridgeTexture.loadFromFile("../FridgeTransparent.png")) {
        cerr << "Error: Could not load FridgeTransparent.png" << endl;
        return -1;
    }
    fridgeTexture.setSmooth(true);
    sf::Sprite fridgeSprite;
    fridgeSprite.setTexture(fridgeTexture);
    float scaleX = static_cast<float>(window.getSize().x) / fridgeTexture.getSize().x * 0.5f;
    float scaleY = static_cast<float>(window.getSize().y) / fridgeTexture.getSize().y * 0.5f;
    float scale = std::min(scaleX, scaleY);
    fridgeSprite.setScale(scale, scale);
    sf::FloatRect spriteBounds = fridgeSprite.getGlobalBounds();
    fridgeSprite.setPosition((window.getSize().x - spriteBounds.width) / 2.0f, (window.getSize().y - spriteBounds.height) / 3.0f);
    sf::Text titleText("Welcome to Fridge", font, 50);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition((window.getSize().x - titleText.getGlobalBounds().width) / 2.0f, fridgeSprite.getPosition().y + spriteBounds.height + 40.0f);

    // Load right arrow texture
    sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("../rightarrow.png")) {
        cerr << "Error: Could not load rightarrow.png" << endl;
        return -1;
    }
    arrowTexture.setSmooth(true);
    sf::Sprite rightArrow;
    rightArrow.setTexture(arrowTexture);
    rightArrow.setScale(0.4f, 0.4f);
    sf::FloatRect arrowBounds = rightArrow.getGlobalBounds();
    rightArrow.setPosition(window.getSize().x - arrowBounds.width - 150.0f, (window.getSize().y - arrowBounds.height) / 2.0f);

    // Load left arrow texture
    sf::Texture leftArrowTexture;
    if (!leftArrowTexture.loadFromFile("../leftarrow.png")) {
        cerr << "Error: Could not load leftarrow.png" << endl;
        return -1;
    }
    leftArrowTexture.setSmooth(true);
    sf::Sprite leftArrow;
    leftArrow.setTexture(leftArrowTexture);
    leftArrow.setScale(0.4f, 0.4f);
    sf::FloatRect leftArrowBounds = leftArrow.getGlobalBounds();
    leftArrow.setPosition(150.0f, (window.getSize().y - leftArrowBounds.height) / 2.0f);

    // Page 2 elements (Preferences)
    sf::Text page2Question("Which ingredients would you like to use?", font, 40);
    page2Question.setFillColor(sf::Color::White);
    page2Question.setPosition((window.getSize().x - page2Question.getGlobalBounds().width) / 2.0f, 100.0f);
    sf::RectangleShape inputBox(sf::Vector2f(400.0f, 50.0f));
    inputBox.setFillColor(sf::Color(255, 255, 255, 100));
    inputBox.setPosition((window.getSize().x - inputBox.getSize().x) / 2.0f, 200.0f);
    sf::Text userInput("", font, 30);
    userInput.setFillColor(sf::Color::Black);
    userInput.setPosition(inputBox.getPosition().x + 10.0f, inputBox.getPosition().y + 10.0f);
    string currentInput = "";

    // Page 3 elements (Avoidances)
    sf::Text page3Question("Which ingredients would you like to avoid?", font, 40);
    page3Question.setFillColor(sf::Color::White);
    page3Question.setPosition((window.getSize().x - page3Question.getGlobalBounds().width) / 2.0f, 100.0f);

    // Page 4 elements (Prioritization)
    sf::Text page4Question("How would you prioritize these qualities?", font, 40);
    page4Question.setFillColor(sf::Color::White);
    page4Question.setPosition((window.getSize().x - page4Question.getGlobalBounds().width) / 2.0f, 100.0f);

    vector<string> categories = {"Cook Time", "Calorie Count", "Popularity"};
    vector<vector<sf::RectangleShape>> priorityBoxes(3, vector<sf::RectangleShape>(3));
    vector<sf::Text> priorityTexts;
    for (int i = 0; i < 3; ++i) {
        sf::Text categoryText(categories[i], font, 30);
        categoryText.setFillColor(sf::Color::White);
        categoryText.setPosition(150.0f, 200.0f + i * 100.0f);
        priorityTexts.push_back(categoryText);
        for (int j = 0; j < 3; ++j) {
            priorityBoxes[i][j].setSize(sf::Vector2f(50.0f, 50.0f));
            priorityBoxes[i][j].setFillColor(sf::Color::White);
            priorityBoxes[i][j].setPosition(400.0f + j * 100.0f, 200.0f + i * 100.0f);
        }
    }

    // Create gradient background
    sf::VertexArray gradient(sf::Quads, 4);
    gradient[0].position = sf::Vector2f(0, 0);
    gradient[1].position = sf::Vector2f(window.getSize().x, 0);
    gradient[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
    gradient[3].position = sf::Vector2f(0, window.getSize().y);

    // Set the colors for gradient
    gradient[0].color = sf::Color(0x72, 0xd1, 0x84, 255); // Top color (#72d184)
    gradient[1].color = sf::Color(0x72, 0xd1, 0x84, 255); // Top color (#72d184)
    gradient[2].color = sf::Color(0x3a, 0x6c, 0xd8, 255); // Bottom color (#3a6cd8)
    gradient[3].color = sf::Color(0x3a, 0x6c, 0xd8, 255); // Bottom color (#3a6cd8)

    float alpha = 0.0f;
    bool fadeIn = true;
    bool fadeOut = false;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Handle arrow button clicks
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (rightArrow.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    if (currentPage < 4) {
                        fadeOut = true;
                        clock.restart();
                    }
                } else if (leftArrow.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && currentPage > 1) {
                    fadeOut = true;
                    clock.restart();
                }
            }

            // Handle text input for ingredient pages
            if (currentPage == 2 || currentPage == 3) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8 && !currentInput.empty()) { // Handle backspace
                        currentInput.pop_back();
                    } else if (event.text.unicode < 128 && event.text.unicode != 13) { // Handle valid input
                        currentInput += static_cast<char>(event.text.unicode);
                    } else if (event.text.unicode == 13 && !currentInput.empty()) { // Handle enter
                        if (currentPage == 2) {
                            preferences.push_back(currentInput);
                        } else {
                            avoidances.push_back(currentInput);
                        }
                        currentInput = "";
                    }
                    userInput.setString(currentInput);
                }
            }
        }

        // Fade in/out
        float deltaTime = clock.restart().asSeconds();
        if (fadeIn) {
            alpha += 250.0f * deltaTime; // Fade in elements faster
            if (alpha >= 255.0f) {
                alpha = 255.0f;
                fadeIn = false;
            }
        } else if (fadeOut) {
            alpha -= 250.0f * deltaTime; // Fade out elements faster
            if (alpha <= 0.0f) {
                alpha = 0.0f;
                fadeOut = false;
                fadeIn = true;
                currentPage = (currentPage < 4) ? currentPage + 1 : 1;
                clock.restart();
            }
        }

        sf::Color fadeColor(255, 255, 255, static_cast<sf::Uint8>(alpha));
        titleText.setFillColor(fadeColor);
        fridgeSprite.setColor(fadeColor);
        rightArrow.setColor(fadeColor);
        doneButton.setFillColor(fadeColor);
        page2Question.setFillColor(fadeColor);
        page3Question.setFillColor(fadeColor);
        page4Question.setFillColor(fadeColor);
        inputBox.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
        userInput.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
        for (auto &text : priorityTexts) text.setFillColor(fadeColor);
        for (auto &row : priorityBoxes) {
            for (auto &box : row) {
                box.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
            }
        }

        // Clear window
        window.clear();

        // Draw gradient background
        window.draw(gradient);

        // Draw current page elements
        if (currentPage == 1) {
            window.draw(fridgeSprite);
            window.draw(titleText);
            window.draw(rightArrow);
        } else if (currentPage == 2) {
            window.draw(page2Question);
            window.draw(inputBox);
            window.draw(userInput);
            window.draw(doneButton);
            window.draw(rightArrow);
            if (currentPage > 1) {
                window.draw(leftArrow);
            }
        } else if (currentPage == 3) {
            window.draw(page3Question);
            window.draw(inputBox);
            window.draw(userInput);
            window.draw(doneButton);
            window.draw(rightArrow);
            window.draw(leftArrow);
        } else if (currentPage == 4) {
            window.draw(page4Question);
            for (int i = 0; i < 3; ++i) {
                window.draw(priorityTexts[i]);
                for (int j = 0; j < 3; ++j) {
                    window.draw(priorityBoxes[i][j]);
                }
            }
            window.draw(doneButton);
            window.draw(leftArrow);
        }

        // Display contents of window
        window.display();
    }

    return 0;
}
