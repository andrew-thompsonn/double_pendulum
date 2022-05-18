#ifndef _PENDULUM_H_
#define _PENDULUM_H_

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <stdlib.h>

#include "constants.h"

#define PI 3.14159

#define INITIAL_THETA_1 PI/2.0f
#define INITIAL_THETA_2 3*PI/5.0f

#define MASS_1 2.0f
#define MASS_2 2.0f
#define TOTAL_MASS 4.0f

#define LENGTH 1.0f
#define LENGTH_SCALAR 195.0f
#define TOTAL_LENGTH 2.0f

#define MASS_SIZE 6.0f

#define TRACE_ENABLE

#define FPS 60.0f
#define G 9.802f

class Pendulum {

    float theta1dot;

    float theta2dot;

    float originX;

    float originY;

    float massSize1;

    float massSize2;

    std::vector<sf::Vertex> vertices;

public:
    
    float theta1;

    float theta2;
    
    float mass1;

    float mass2;

    float length1;

    float length2;

    void init();

    void update();

    void draw(sf::RenderWindow &window);

    void reset();
};

#endif /* _PENDULUM_H_ */