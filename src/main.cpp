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

    sf::Clock timer;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                continue;
            }
        }
        window.clear(sf::Color::Black);

        pendulum.update();
        pendulum.draw(window);

        window.display();
    }
    return EXIT_SUCCESS;
}