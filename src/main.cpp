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
    timerText.setPosition(WIN_SIZE_X - 30, WIN_SIZE_Y - CELL_SIZE);
    
    sf::Text angleText;
    angleText.setFont(timerFont);
    angleText.setCharacterSize(12);
    angleText.setFillColor(sf::Color(105, 105, 105));
    angleText.setPosition(30, WIN_SIZE_Y - 6*CELL_SIZE);

    sf::Text resetText;
    resetText.setFont(timerFont);
    resetText.setCharacterSize(12);
    resetText.setFillColor(sf::Color(105, 105, 105));
    resetText.setPosition(30, CELL_SIZE);
    resetText.setString("Reset <R>");
    
    char angleBuffer[0xFF];
    char timeBuffer[0xFF];

    sprintf(angleBuffer, "t1 = %.1f [deg]\nt2 = %.1f [deg]\n\nm1 = %.1f [kg]\nm2 = %.1f [kg]\n\nl1 = %.1f [m]\nl2 = %.1f [m] ", 
            pendulum.theta1*180/PI, pendulum.theta2*180/PI, pendulum.mass1, pendulum.mass2, 
            pendulum.length1, pendulum.length2);
    angleText.setString(angleBuffer);

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
                sprintf(angleBuffer, "t1 = %.1f [deg]\nt2 = %.1f [deg]\n\nm1 = %.1f [kg]\nm2 = %.1f [kg]\n\nl1 = %.1f [m]\nl2 = %.1f [m] ", 
                        pendulum.theta1*180/PI, pendulum.theta2*180/PI, pendulum.mass1, pendulum.mass2, 
                        pendulum.length1, pendulum.length2);
                angleText.setString(angleBuffer);
            }
        }
        window.clear(sf::Color(0, 12, 26));

        int time = timer.getElapsedTime().asSeconds();
        sprintf(timeBuffer, "%d s", time);
        timerText.setString(timeBuffer);

        pendulum.update();
        pendulum.draw(window);

        window.draw(timerText);
        window.draw(angleText);
        window.draw(resetText);
        window.display();
    }
    return EXIT_SUCCESS;
}