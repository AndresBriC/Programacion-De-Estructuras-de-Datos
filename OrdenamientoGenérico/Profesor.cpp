#include "Profesor.h"
#include <string>
#include <iostream>

using namespace std;

Profesor::Profesor(string nom, int numNom, string dept){
    nombre = nom;
    numNomina = numNom;
    departamento = dept;
}

void Profesor::muestraDatos(){
    cout << "Nombre: " << nombre << endl;
    cout << "Numero nomina: " << numNomina << endl;
    cout << "Departamento: " << departamento << endl;
}
