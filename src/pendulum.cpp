#include "pendulum.h"

void Pendulum::init() {
    
    theta1 = INITIAL_THETA_1;
    theta2 = INITIAL_THETA_2;

    theta1dot = 0; 
    theta2dot = 0;

    mass1 = MASS_1;
    mass2 = MASS_2;

    length1 = LENGTH;
    length2 = LENGTH;
    
    originX = WIN_SIZE_X/2.0f;
    originY = WIN_SIZE_Y/4.0f;

    frameCount = 0;
}

void Pendulum::update() {

    float term1A = -G*(2*mass1 + mass2)*sinf(theta1);
    float term1B = -mass2*G*sinf(theta1 - 2*theta2);
    float term1C = -2*sinf(theta1 - theta2)*mass2*(powf(theta2dot, 2.0f)*length2 + 
                    powf(theta1dot, 2.0f)*length1*cosf(theta1 - theta2));

    float denominator1 = length1*(2*mass1 + mass2 - mass2*cosf(2*theta1 - 2*theta2));
    float theta1ddot = (term1A + term1B + term1C)/denominator1;

    float term2A = 2*sinf(theta1-theta2);
    float term2B = (powf(theta1dot, 2.0f)*length1*(mass1 + mass2));
    float term2C = G*(mass1 + mass2)*cosf(theta1);
    float term2D = powf(theta2dot, 2.0f)*length2*mass2*cosf(theta1 - theta2);

    float denominator2 = length2*(2*mass1 + mass2 - mass2*cosf(2*theta1 - 2*theta2));
    float theta2ddot = term2A*(term2B + term2C + term2D)/denominator2;

    float deltaTime = 1.0f/FPS;

    theta1dot += deltaTime * theta1ddot;
    theta2dot += deltaTime * theta2ddot;

    theta1 += deltaTime * theta1dot;
    theta2 += deltaTime * theta2dot;
}

void Pendulum::draw(sf::RenderWindow &window) {

    sf::CircleShape root(MASS_SIZE);
    root.setFillColor(sf::Color::Red);
    root.setPosition(originX, originY);

    float positionX1 = length1*sinf(theta1)*LENGTH_SCALAR;
    float positionY1 = length1*cosf(theta1)*LENGTH_SCALAR;

    sf::CircleShape mass1(MASS_SIZE);
    mass1.setFillColor(sf::Color::Blue);
    mass1.setPosition(originX + positionX1, originY + positionY1);

    float positionX2 = positionX1 + length2*sinf(theta2)*LENGTH_SCALAR;
    float positionY2 = positionY1 + length2*cosf(theta2)*LENGTH_SCALAR;

    sf::CircleShape mass2(MASS_SIZE);
    mass2.setFillColor(sf::Color::Blue);
    mass2.setPosition(originX + positionX2, originY + positionY2);

    sf::Vertex line1[] = {
        sf::Vertex(sf::Vector2f(originX + MASS_SIZE, originY + MASS_SIZE)),
        sf::Vertex(sf::Vector2f(originX + positionX1 + MASS_SIZE, originY + positionY1 + MASS_SIZE))
    };
    window.draw(line1, 2, sf::Lines);
    
    sf::Vertex line2[] = {
        sf::Vertex(sf::Vector2f(originX + positionX1 + MASS_SIZE, originY + positionY1 + MASS_SIZE)),
        sf::Vertex(sf::Vector2f(originX + positionX2 + MASS_SIZE, originY + positionY2 + MASS_SIZE))
    };
    window.draw(line2, 2, sf::Lines);
    
    window.draw(root);
    window.draw(mass1);
    window.draw(mass2);
}