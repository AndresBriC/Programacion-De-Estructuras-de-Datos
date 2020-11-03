#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

class Fecha{
private:
    int dia, mes, anio;

public:
    //Constructores
    Fecha();
    Fecha(int cDia, int cMes, int cAnio);

    //Accessors
    int getDia();
    int getMes();
    int getAnio();

    //Mutators
    void setDia(int mDia);
    void setMes(int mMes);
    void setAnio(int mAnio);

    //Sobrecarga de operadores
    friend ostream & operator<<(ostream & os, const Fecha & fecha);
    friend bool operator!= (const Fecha &f1, const Fecha &f2);
    friend bool operator== (const Fecha &f1, const Fecha &f2);
    friend bool operator> (const Fecha &f1, const Fecha &f2);
    friend bool operator< (const Fecha &f1, const Fecha &f2);

    //Funciones complementarias
    Fecha stringToFecha(string);
    string vectorToString(vector<char>);

};

#endif // FECHA_H_INCLUDED
