#ifndef PROFESOR_H_INCLUDED
#define PROFESOR_H_INCLUDED
#include <string>

using namespace std;

class Profesor{

private:
    int numNomina;
    string departamento, nombre;

public:
    Profesor(string nom, int numNom, string dept);
    void muestraDatos();
};


#endif // PROFESOR_H_INCLUDED
