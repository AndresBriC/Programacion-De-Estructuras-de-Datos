#include <iostream>

#include "Fecha.h"

using namespace std;

//Constructores
Fecha::Fecha(){
    dia = 0;
    mes = 0;
    anio = 0;
}

Fecha::Fecha(int cDia, int cMes, int cAnio){
    dia = cDia;
    mes = cMes;
    anio = cAnio;
}

//Sobrecarga de operadores
ostream & operator<<(ostream & os, const Fecha & fecha){
    os << fecha.dia<< "-";
    os << fecha.mes<< "-";
    os << fecha.anio;

    return os;
}

bool operator== (const Fecha &f1, const Fecha &f2){
    return f1.dia == f2.dia && f1.mes == f2.mes && f1.anio == f2.anio;
}

bool operator!= (const Fecha &f1, const Fecha &f2){
    return !(f1 == f2);
}

bool operator> (const Fecha &f1, const Fecha &f2){
    return f1.anio > f2.anio || (f1.anio == f2.anio && f1.mes > f2.mes) || (f1.anio == f2.anio && f1.mes == f2.mes && f1.dia > f2.dia);
}

bool operator< (const Fecha &f1, const Fecha &f2){
    return f1.anio < f2.anio || (f1.anio == f2.anio && f1.mes < f2.mes) || (f1.anio == f2.anio && f1.mes == f2.mes && f1.dia < f2.dia);
}

//Accessors
int Fecha::getDia(){
    return dia;
}

int Fecha::getMes(){
    return mes;
}

int Fecha::getAnio(){
    return anio;
}


//Mutators
void Fecha::setDia(int mDia){
    dia = mDia;
}

void Fecha::setMes(int mMes){
    mes = mMes;
}

void Fecha::setAnio(int mAnio){
    anio = mAnio;
}
