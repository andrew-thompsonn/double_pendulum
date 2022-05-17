#!/bin/bash

g++ -IC:/SFML/include -c src/main.cpp -o bin/main.o
g++ -IC:/SFML/include -c src/pendulum.cpp -o bin/pendulum.o
g++ -LC:/SFML/lib -o bin/app.exe bin/main.o bin/pendulum.o -lmingw32 -lm -lsfml-system -lsfml-window -lsfml-graphics -lsfml-main