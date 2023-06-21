#include "black_box/Application.h"
#include "World.h"
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Please, call with one argument ( example: ./physics <путь к файлу smile.txt> )";
        return 1;
    } else {
        World w(argv[1]);
        /**
         * Код ниже запускает выполнение приложения. Для
         * выполнения задания нет необходимости изучать
         * или менять содержимое Application. Для начала
         * лучше сфокусироваться на Ball.hpp, Ball.cpp и
         * World.cpp
         */
        Application app("physics");
        app.run(w);
    }
}