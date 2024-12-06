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
#include "reading.cpp"

using namespace std;

void displayRecipesWindow(vector<Recipe> recipes, sf::Font &font) {
    sf::RenderWindow recipesWindow(sf::VideoMode(800, 600), "Top 5 Recipes", sf::Style::Close);

    vector<sf::Text> recipeTexts;
    for (size_t i = 0; i < recipes.size(); ++i) {
        sf::Text recipeText;
        recipeText.setFont(font);
        recipeText.setCharacterSize(20);
        recipeText.setFillColor(sf::Color::White);

        stringstream ss;
        ss << "Name: " << recipes[i].name << "\n"
           << "Cook Time: " << recipes[i].total_time << " min\n"
           << "Rating: " << recipes[i].rating << "\n"
           << "Calories: " << recipes[i].calories << "\n"
           << "Ingredients: ";
        for (const auto &ingredient : recipes[i].ingredients) {
            ss << ingredient << ", ";
        }
        string recipeInfo = ss.str();
        recipeInfo.pop_back();
        recipeInfo.pop_back(); // Remove trailing comma and space

        recipeText.setString(recipeInfo);
        recipeText.setPosition(20, 30 + i * 120);
        recipeTexts.push_back(recipeText);
    }

    while (recipesWindow.isOpen()) {
        sf::Event event;
        while (recipesWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                recipesWindow.close();
            }
        }

        recipesWindow.clear();
        for (const auto &text : recipeTexts) {
            recipesWindow.draw(text);
        }
        recipesWindow.display();
    }
}

int main() {

    // Check if the font file exists
    namespace fs = std::filesystem;
    if (fs::exists("../Ubuntu/Ubuntu-Regular.ttf")) {
        std::cout << "Font file found!" << std::endl;
    } else {
        std::cout << "Font file not found." << std::endl;
        return -1;
    }

    // Create a window that fills the entire screen
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Fridge App", sf::Style::Fullscreen);

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("../Ubuntu/Ubuntu-Regular.ttf")) {
        cerr << "Error: Could not load Ubuntu/Ubuntu-Regular.ttf" << endl;
        return -1;
    }

    // Page management
    int currentPage = 1;
    vector<string> preferences;
    vector<string> avoidances;
    vector<string> priorities;
    bool inputActive = false;
    bool avoidInputActive = false;
    bool showCursor = false;
    sf::Clock cursorClock;

    // Elements for page 1 (Logo, Title, and Begin Button)
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
    fridgeSprite.setPosition((window.getSize().x - spriteBounds.width) / 2.0f, (window.getSize().y - spriteBounds.height) / 4.0f);
    sf::Text titleText("Welcome to Fridge", font, 50);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition((window.getSize().x - titleText.getGlobalBounds().width) / 2.0f, fridgeSprite.getPosition().y + spriteBounds.height + 0.0f);

    // Load Begin and Done button textures
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("../button.png")) {
        cerr << "Error: Could not load button.png" << endl;
        return -1;
    }
    buttonTexture.setSmooth(true);

    // Create Begin button sprite
    sf::Sprite beginButton;
    beginButton.setTexture(buttonTexture);
    beginButton.setScale(0.5f, 0.5f);
    sf::FloatRect beginButtonBounds = beginButton.getGlobalBounds();
    beginButton.setPosition((window.getSize().x - beginButtonBounds.width) / 2.0f, titleText.getPosition().y + 60.0f);

    sf::Text beginButtonText("BEGIN", font, 30);
    beginButtonText.setFillColor(sf::Color::Black);
    beginButtonText.setStyle(sf::Text::Bold);
    beginButtonText.setPosition(
            beginButton.getPosition().x + (beginButtonBounds.width - beginButtonText.getGlobalBounds().width) / 2.0f,
            beginButton.getPosition().y + (beginButtonBounds.height - beginButtonText.getGlobalBounds().height) / 2.0f - 10.0f
    );

    // Create Done button sprite
    sf::Sprite doneButton;
    doneButton.setTexture(buttonTexture);
    doneButton.setScale(0.5f, 0.5f);
    doneButton.setPosition(beginButton.getPosition());

    sf::Text doneButtonText("DONE", font, 30);
    doneButtonText.setFillColor(sf::Color::Black);
    doneButtonText.setStyle(sf::Text::Bold);
    doneButtonText.setPosition(
            doneButton.getPosition().x + (beginButtonBounds.width - doneButtonText.getGlobalBounds().width) / 2.0f,
            doneButton.getPosition().y + (beginButtonBounds.height - doneButtonText.getGlobalBounds().height) / 2.0f - 10.0f
    );

    // Elements for page 2 (Merged Preferences and Avoidances)
    sf::Text page2Question("Which ingredients would you like to use?", font, 40);
    page2Question.setFillColor(sf::Color::White);
    page2Question.setPosition((window.getSize().x - page2Question.getGlobalBounds().width) / 2.0f, 200.0f);
    sf::RectangleShape inputBox(sf::Vector2f(700.0f, 50.0f));
    inputBox.setFillColor(sf::Color(255, 255, 255, 100));
    inputBox.setPosition((window.getSize().x - inputBox.getSize().x) / 2.0f, 300.0f);
    sf::Text userInput("|", font, 30);
    userInput.setFillColor(sf::Color::Black);
    userInput.setPosition(inputBox.getPosition().x + inputBox.getSize().x / 2.0f, inputBox.getPosition().y + 5.0f);
    string currentInput = "";

    sf::Text page3Question("Which ingredients would you like to avoid?", font, 40);
    page3Question.setFillColor(sf::Color::White);
    page3Question.setPosition((window.getSize().x - page3Question.getGlobalBounds().width) / 2.0f, 500.0f);
    sf::RectangleShape avoidInputBox(sf::Vector2f(700.0f, 50.0f));
    avoidInputBox.setFillColor(sf::Color(255, 255, 255, 100));
    avoidInputBox.setPosition((window.getSize().x - avoidInputBox.getSize().x) / 2.0f, 600.0f);
    sf::Text avoidUserInput("|", font, 30);
    avoidUserInput.setFillColor(sf::Color::Black);
    avoidUserInput.setPosition(avoidInputBox.getPosition().x + inputBox.getSize().x / 2.0f, avoidInputBox.getPosition().y + 5.0f);
    string avoidCurrentInput = "";

    // Elements for page 3 (Prioritization)
    sf::Text page4Question("How would you prioritize these qualities?", font, 40);
    page4Question.setFillColor(sf::Color::White);
    page4Question.setPosition((window.getSize().x - page4Question.getGlobalBounds().width) / 2.0f, 200.0f);

    sf::Text page4Context("Click in the order you would rank them, starting with high priority", font, 20);
    page4Context.setFillColor(sf::Color::White);
    page4Context.setPosition((window.getSize().x - page4Context.getGlobalBounds().width) / 2.0f, 265.0f);

    // Load icons for cook time, popularity, and calorie count
    sf::Texture cookTimeTexture;
    if (!cookTimeTexture.loadFromFile("../cooktime.png")) {
        cerr << "Error: Could not load cooktime.png" << endl;
        return -1;
    }
    sf::Texture popularityTexture;
    if (!popularityTexture.loadFromFile("../popularity.png")) {
        cerr << "Error: Could not load popularity.png" << endl;
        return -1;
    }
    sf::Texture calorieTexture;
    if (!calorieTexture.loadFromFile("../calorie.png")) {
        cerr << "Error: Could not load calorie.png" << endl;
        return -1;
    }

    // Load textures for hovered versions of icons
    sf::Texture cookTimeTexture2;
    if (!cookTimeTexture2.loadFromFile("../cooktime2.png")) {
        cerr << "Error: Could not load cooktime2.png" << endl;
        return -1;
    }
    sf::Texture popularityTexture2;
    if (!popularityTexture2.loadFromFile("../popularity2.png")) {
        cerr << "Error: Could not load popularity2.png" << endl;
        return -1;
    }
    sf::Texture calorieTexture2;
    if (!calorieTexture2.loadFromFile("../calorie2.png")) {
        cerr << "Error: Could not load calorie2.png" << endl;
        return -1;
    }

    // Create sprites for the icons
    sf::Sprite cookTimeSprite;
    cookTimeSprite.setTexture(cookTimeTexture);
    cookTimeSprite.setScale(0.5f, 0.5f);
    sf::FloatRect cookTimeBounds = cookTimeSprite.getGlobalBounds();
    cookTimeSprite.setPosition((window.getSize().x / 8.0f * 2.0f) - (cookTimeBounds.width / 2.0f), 350.0f);

    sf::Sprite popularitySprite;
    popularitySprite.setTexture(popularityTexture);
    popularitySprite.setScale(0.5f, 0.5f);
    sf::FloatRect popularityBounds = popularitySprite.getGlobalBounds();
    popularitySprite.setPosition((window.getSize().x / 2.0f) - (popularityBounds.width / 2.0f), 350.0f);

    sf::Sprite calorieSprite;
    calorieSprite.setTexture(calorieTexture);
    calorieSprite.setScale(0.5f, 0.5f);
    sf::FloatRect calorieBounds = calorieSprite.getGlobalBounds();
    calorieSprite.setPosition((window.getSize().x / 8.0f * 6.0f) - (calorieBounds.width / 2.0f), 350.0f);

    sf::Text prioritiesDisplay("Your Priorities: N/A", font, 30);
    prioritiesDisplay.setFillColor(sf::Color::White);
    prioritiesDisplay.setPosition((window.getSize().x - prioritiesDisplay.getGlobalBounds().width) / 2.0f, calorieSprite.getPosition().y + calorieSprite.getGlobalBounds().height + 300);

    // Create a gradient background (top to bottom gradient)
    sf::VertexArray gradient(sf::Quads, 4);
    gradient[0].position = sf::Vector2f(0, 0);
    gradient[1].position = sf::Vector2f(window.getSize().x, 0);
    gradient[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
    gradient[3].position = sf::Vector2f(0, window.getSize().y);

    // Set the colors for the gradient (top to bottom)
    gradient[0].color = sf::Color(0x72, 0xd1, 0x84, 255); // Top color (#72d184)
    gradient[1].color = sf::Color(0x72, 0xd1, 0x84, 255); // Top color (#72d184)
    gradient[2].color = sf::Color(0x3a, 0x6c, 0xd8, 255); // Bottom color (#3a6cd8)
    gradient[3].color = sf::Color(0x3a, 0x6c, 0xd8, 255); // Bottom color (#3a6cd8)

    // Set initial alpha for elements
    float alpha = 0.0f;
    bool fadeIn = true;
    bool fadeOut = false;
    bool moveButtonDown = false;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Handle button click
            if (currentPage == 1 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (beginButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    fadeOut = true;
                    clock.restart();
                }
            } else if ((currentPage == 2 || currentPage == 3) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (doneButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    fadeOut = true;
                    clock.restart();
                }
            }

            // Handle text input
            if (currentPage == 2 && inputActive && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!currentInput.empty()) {
                        currentInput.pop_back();
                    }
                } else if (event.text.unicode < 128) {
                    currentInput += static_cast<char>(event.text.unicode);
                }
                userInput.setString(currentInput + (showCursor ? '|' : ' '));
                userInput.setPosition(inputBox.getPosition().x + (inputBox.getSize().x - userInput.getLocalBounds().width) / 2.0f, inputBox.getPosition().y + 5.0f);
            }

            if (currentPage == 2 && avoidInputActive && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!avoidCurrentInput.empty()) {
                        avoidCurrentInput.pop_back();
                    }
                } else if (event.text.unicode < 128) {
                    avoidCurrentInput += static_cast<char>(event.text.unicode);
                }
                avoidUserInput.setString(avoidCurrentInput + (showCursor ? '|' : ' '));
                avoidUserInput.setPosition(avoidInputBox.getPosition().x + (avoidInputBox.getSize().x - avoidUserInput.getLocalBounds().width) / 2.0f, avoidInputBox.getPosition().y + 5.0f);
            }

            // Handle mouse click to activate/deactivate input boxes
            if (currentPage == 2 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                if (inputBox.getGlobalBounds().contains(mousePos)) {
                    inputActive = true;
                    avoidInputActive = false;
                } else if (avoidInputBox.getGlobalBounds().contains(mousePos)) {
                    inputActive = false;
                    avoidInputActive = true;
                } else {
                    inputActive = false;
                    avoidInputActive = false;
                }
            }

            // Handle Enter key to add input to vectors
            if (currentPage == 2 && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (inputActive && !currentInput.empty()) {
                    preferences.push_back(currentInput);
                    currentInput.clear();
                    userInput.setString("|");
                } else if (avoidInputActive && !avoidCurrentInput.empty()) {
                    avoidances.push_back(avoidCurrentInput);
                    avoidCurrentInput.clear();
                    avoidUserInput.setString("|");
                }
            }

            // Handle icon clicks for setting priorities
            if (currentPage == 3 && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

                if (cookTimeSprite.getGlobalBounds().contains(mousePos) &&
                    find(priorities.begin(), priorities.end(), "cook_time") == priorities.end()) {
                    priorities.push_back("cook_time");
                } else if (popularitySprite.getGlobalBounds().contains(mousePos) &&
                           find(priorities.begin(), priorities.end(), "rating") == priorities.end()) {
                    priorities.push_back("rating");
                } else if (calorieSprite.getGlobalBounds().contains(mousePos) &&
                           find(priorities.begin(), priorities.end(), "calories") == priorities.end()) {
                    priorities.push_back("calories");
                }
            }

        }

        if (currentPage == 3) {
            if (priorities.empty()) {
                prioritiesDisplay.setString("Your Priorities: N/A");
            } else {
                string displayText = "Your Priorities: ";
                for (size_t i = 0; i < priorities.size(); ++i) {
                    string priorityText;
                    if (i == 0) {
                        priorityText = "(High)";
                    } else if (i == 1) {
                        priorityText = "(Medium)";
                    } else if (i == 2) {
                        priorityText = "(Low)";
                    }

                    if (priorities[i] == "cook_time") {
                        displayText += "Cook Time " + priorityText;
                    } else if (priorities[i] == "rating") {
                        displayText += "Rating " + priorityText;
                    } else if (priorities[i] == "calories") {
                        displayText += "Calories " + priorityText;
                    }

                    if (i < priorities.size() - 1) {
                        displayText += ", ";
                    }
                }
                prioritiesDisplay.setString(displayText);
            }

            // Update the position of the priorities display
            prioritiesDisplay.setPosition((window.getSize().x - prioritiesDisplay.getGlobalBounds().width) / 2.0f, calorieSprite.getPosition().y + calorieSprite.getGlobalBounds().height + 50);
        }

        // Blinking cursor logic
        if (cursorClock.getElapsedTime().asSeconds() >= 0.5f) {
            showCursor = !showCursor;
            cursorClock.restart();
            if (inputActive) {
                userInput.setString(currentInput + (showCursor ? '|' : ' '));
            } else if (avoidInputActive) {
                avoidUserInput.setString(avoidCurrentInput + (showCursor ? '|' : ' '));
            }
        }

        // Update button color when hovering
        if (currentPage == 1) {
            if (beginButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                beginButton.setColor(sf::Color(200, 200, 200)); // Light grey when hovered
            } else {
                beginButton.setColor(sf::Color(255, 255, 255)); // Default white
            }
        } else {
            if (doneButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                doneButton.setColor(sf::Color(200, 200, 200)); // Light grey when hovered
            } else {
                doneButton.setColor(sf::Color(255, 255, 255)); // Default white
            }
        }

        // Handle icon hovering on page 3
        if (currentPage == 3) {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            if (cookTimeSprite.getGlobalBounds().contains(mousePos)) {
                cookTimeSprite.setTexture(cookTimeTexture2);
            } else {
                cookTimeSprite.setTexture(cookTimeTexture);
            }

            if (popularitySprite.getGlobalBounds().contains(mousePos)) {
                popularitySprite.setTexture(popularityTexture2);
            } else {
                popularitySprite.setTexture(popularityTexture);
            }

            if (calorieSprite.getGlobalBounds().contains(mousePos)) {
                calorieSprite.setTexture(calorieTexture2);
            } else {
                calorieSprite.setTexture(calorieTexture);
            }
        }

        // Update fade in/out logic
        float deltaTime = clock.restart().asSeconds();
        if (fadeIn) {
            alpha += 250.0f * deltaTime; // Increase alpha to fade in elements faster
            if (alpha >= 255.0f) {
                alpha = 255.0f;
                fadeIn = false;
            }
        } else if (fadeOut) {
            alpha -= 250.0f * deltaTime; // Decrease alpha to fade out elements faster
            if (alpha <= 0.0f) {
                alpha = 0.0f;
                fadeOut = false;
                if (currentPage == 1) {
                    moveButtonDown = true;
                    currentPage = 2;
                    doneButtonText.setString("NEXT");
                    clock.restart();
                } else if (currentPage == 2) {
                    currentPage = 3;
                    doneButtonText.setString("DONE");
                    clock.restart();
                } else if (currentPage == 3) {
                    cout << "Priorities: ";
                    for (int i = 0; i < priorities.size(); i++) {
                        cout << priorities[i] << " ";
                    }
                    window.close(); // Close window when "DONE" is clicked on the last page
                }
                fadeIn = true;
            }
        } else if (moveButtonDown) {
            beginButton.move(0, 100.0f); // Move the button down by 100 pixels
            beginButtonText.move(0, 100.0f); // Move the text down by 100 pixels
            moveButtonDown = false;
            fadeIn = true;
            clock.restart();
        }

        // Set the alpha for all elements
        sf::Color fadeColor(255, 255, 255, static_cast<sf::Uint8>(alpha));
        titleText.setFillColor(fadeColor);
        fridgeSprite.setColor(fadeColor);
        if (currentPage == 1) {
            beginButtonText.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
        } else {
            doneButtonText.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
            if (currentPage == 2) {
                page2Question.setFillColor(fadeColor);
                page3Question.setFillColor(fadeColor);
                inputBox.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
                userInput.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
                avoidInputBox.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
                avoidUserInput.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
            } else if (currentPage == 3) {
                page4Question.setFillColor(fadeColor);
                page4Context.setFillColor(fadeColor);
                cookTimeSprite.setColor(fadeColor);
                popularitySprite.setColor(fadeColor);
                calorieSprite.setColor(fadeColor);

            }
        }

        // Clear the window
        window.clear();

        // Draw the gradient background
        window.draw(gradient);

        // Draw current page elements
        if (currentPage == 1) {
            window.draw(fridgeSprite);
            window.draw(titleText);
            window.draw(beginButton);
            window.draw(beginButtonText);
        } else if (currentPage == 2) {
            window.draw(page2Question);
            window.draw(inputBox);
            window.draw(userInput);
            window.draw(page3Question);
            window.draw(avoidInputBox);
            window.draw(avoidUserInput);
            window.draw(doneButton);
            window.draw(doneButtonText);
        } else if (currentPage == 3) {
            window.draw(page4Question);
            window.draw(page4Context);
            window.draw(cookTimeSprite);
            window.draw(popularitySprite);
            window.draw(calorieSprite);
            window.draw(doneButton);
            window.draw(doneButtonText);
            window.draw(prioritiesDisplay);
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}
