//
//  Fecha.hpp
//  Act_5.2
//
//  Created by inigo guerra on 24/11/20.
//

#ifndef Fecha_hpp
#define Fecha_hpp

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

#endif /* Fecha_hpp */
