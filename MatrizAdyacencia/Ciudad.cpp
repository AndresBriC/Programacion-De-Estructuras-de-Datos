#include <iostream>

#include "Ciudad.h"

Ciudad::Ciudad(){
    nombre = "";
    numHabitantes = 0;
}

Ciudad::Ciudad(std::string _nombre, int _numHabitantes){
    nombre = _nombre;
    numHabitantes = _numHabitantes;
}

Ciudad::~Ciudad(){

}

std::string Ciudad::getNombre(){
    return nombre;
}

int Ciudad::getNumHabitantes(){
    return numHabitantes;
}

std::ostream &operator <<(std::ostream & os, const Ciudad &ciudad){
    os << ciudad.nombre << ", ";
    os << ciudad.numHabitantes;

    return os;
}
