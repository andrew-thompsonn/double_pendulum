#include "pendulum.h"

void Pendulum::init() {

    int randomTheta1 = rand() % 200 + 1;
    int randomTheta2 = rand() % 200 + 1;

    theta1 = (randomTheta1/100.0f)*PI;
    theta2 = (randomTheta2/100.0f)*PI;

    int randomMass = rand() % 50 + 25; 
    
    mass1 = (randomMass/100.0f)*TOTAL_MASS;
    mass2 = TOTAL_MASS - mass1;

    int randomLength = rand() % 50 + 25;
    
    length1 = (randomLength/100.0f)*TOTAL_LENGTH;
    length2 = TOTAL_LENGTH - length1;

    theta1dot = 0; 
    theta2dot = 0;
    
    originX = WIN_SIZE_X/2.0f;
    originY = WIN_SIZE_Y/2.0f;

    massSize1 = 2*(mass1/TOTAL_MASS)*MASS_SIZE;
    massSize2 = 2*(mass2/TOTAL_MASS)*MASS_SIZE;
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

    sf::CircleShape root(MASS_SIZE/2);
    root.setFillColor(sf::Color(0, 102, 51));
    root.setPosition(originX, originY);

    float positionX1 = length1*sinf(theta1)*LENGTH_SCALAR;
    float positionY1 = length1*cosf(theta1)*LENGTH_SCALAR;

    sf::CircleShape mass1(massSize1);
    mass1.setFillColor(sf::Color(204, 102, 0));
    mass1.setPosition(originX + positionX1, originY + positionY1);

    float positionX2 = positionX1 + length2*sinf(theta2)*LENGTH_SCALAR;
    float positionY2 = positionY1 + length2*cosf(theta2)*LENGTH_SCALAR;

    sf::CircleShape mass2(massSize2);
    mass2.setFillColor(sf::Color(204, 102, 0));
    mass2.setPosition(originX + positionX2, originY + positionY2);

    sf::Vertex line1[] = {
        sf::Vertex(sf::Vector2f(originX + MASS_SIZE/2, originY + MASS_SIZE/2)),
        sf::Vertex(sf::Vector2f(originX + positionX1 + massSize1, originY + positionY1 + massSize1))
    };
    
    sf::Vertex line2[] = {
        sf::Vertex(sf::Vector2f(originX + positionX1 + massSize1, originY + positionY1 + massSize1)),
        sf::Vertex(sf::Vector2f(originX + positionX2 + massSize2, originY + positionY2 + massSize2))
    };
    vertices.push_back(sf::Vertex(sf::Vector2f(originX + positionX2 + massSize2, originY + positionY2 + massSize2),
                       sf::Color(105, 105, 105)));
    
#ifdef TRACE_ENABLE
    window.draw(&vertices[0], vertices.size(), sf::LineStrip);
#endif
    window.draw(line2, 2, sf::Lines);
    window.draw(line1, 2, sf::Lines);
    window.draw(root);
    window.draw(mass1);
    window.draw(mass2);
}

void Pendulum::reset() {

    vertices.clear();
    init();
}