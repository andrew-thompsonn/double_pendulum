#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "pendulum.h"
#include "constants.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X+CELL_SIZE, WIN_SIZE_Y+CELL_SIZE),
                            WIN_TITLE, sf::Style::Close);
    window.setVerticalSyncEnabled (true);

    Pendulum pendulum;
    pendulum.init();

    sf::Font timerFont;
    if (!timerFont.loadFromFile("font/ARIALBD.TTF"))
        printf("Unable to load font\n");

    sf::Text timerText;
    timerText.setFont(timerFont);
    timerText.setCharacterSize(12);
    timerText.setFillColor(sf::Color(105, 105, 105));
    timerText.setPosition(50, WIN_SIZE_Y - CELL_SIZE);

    char timeBuffer[0xFF];

    sf::Clock timer;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                continue;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                timer.restart();
                pendulum.reset();
            }
        }
        window.clear(sf::Color(0, 12, 26));

        int time = timer.getElapsedTime().asSeconds();
        sprintf(timeBuffer, "Elapsed Time: %d seconds", time);
        timerText.setString(timeBuffer);

        pendulum.update();
        pendulum.draw(window);

        window.draw(timerText);
        window.display();
    }
    return EXIT_SUCCESS;
}