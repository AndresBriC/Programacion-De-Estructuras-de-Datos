//
//  Registro.hpp
//  Act_3.4
//
//  Created by inigo guerra on 03/11/20.
//

#ifndef Registro_hpp
#define Registro_hpp

#include <string>
#include <iostream>

#include "Fecha.hpp"
#include "Hora.hpp"

using namespace std;

class Registro{
private:
    Fecha fecha;
    Hora hora; //Datos de tiempo
    string ipOrigen, puertoOrigen, nombreOrigen; //Datos de origen
    string ipDestino, nombreDestino;//Datos de destino
    int puertoDestino;

public:
    //Constructores
    Registro();
    Registro(Fecha cFecha, Hora cHora, string cIpOrigen, string cPuertoOrigen, string cNombreOrigen, string cIpDestino, int cPuertoDestino, string cNombreDestino);

    //Accesors
    Fecha getFecha();
    Hora getHora();
    string getIpOrigen();
    string getPuertoOrigen();
    string getNombreOrigen();
    string getIpDestino();
    int getPuertoDestino();
    string getNombreDestino();

    //Mutators
    void setFecha(Fecha sFecha);
    void setHora(Hora sHora);
    void setIpOrigen(string sIpOrigen);
    void setPuertoOrigen(string sPuertoOrigen);
    void setNombreOrigen(string sNombreOrigen);
    void setIpDestino(string sIpDestino);
    void setPuertoDestino(int sPuuertoDestino);
    void setNombreDestino(string sNombreDestino);

    //Sobrecarga de operadores
    friend ostream & operator<<(ostream & os, const Registro & registro);

};

#endif // REGISTRO_H_INCLUDED
