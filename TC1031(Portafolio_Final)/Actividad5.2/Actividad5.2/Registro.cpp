//
//  Registro.cpp
//  Act_5.2
//
//  Created by inigo guerra on 24/11/20.
//

#include "Registro.hpp"
#include <iostream>

using namespace std;

//Constructores
Registro::Registro(){
    ipOrigen = "";
    puertoOrigen = "";
    nombreOrigen = "";
    ipDestino = "";
    puertoDestino = 0;
    nombreDestino = "";
}

Registro::Registro(Fecha cFecha, Hora cHora, string cIpOrigen, string cPuertoOrigen, string cNombreOrigen, string cIpDestino, int cPuertoDestino, string cNombreDestino){
    fecha = cFecha;
    hora = cHora;
    ipOrigen = cIpOrigen;
    puertoOrigen = cPuertoOrigen;
    nombreOrigen = cNombreOrigen;
    ipDestino = cIpDestino;
    puertoDestino = cPuertoDestino;
    nombreDestino = cNombreDestino;
}

//Sobrecarga de operadores
ostream & operator<<(ostream & os, const Registro & registro){
    os << registro.fecha << ", ";
    os << registro.hora << ", ";
    os << registro.ipOrigen << ", ";
    os << registro.puertoOrigen << ", ";
    os << registro.nombreOrigen << ", ";
    os << registro.ipDestino << ", ";
    os << registro.puertoDestino;
    os << registro.nombreDestino;

    return os;
}

//Accessors
Fecha Registro::getFecha(){
    return fecha;
}

Hora Registro::getHora(){
    return hora;
}

string Registro::getIpOrigen(){
    return ipOrigen;
}

string Registro::getPuertoOrigen(){
    return puertoOrigen;
}

string Registro::getNombreOrigen(){
    return nombreOrigen;
}

string Registro::getIpDestino(){
    return ipDestino;
}

int Registro::getPuertoDestino(){
    return puertoDestino;
}

string Registro::getNombreDestino(){
    return nombreDestino;
}

//Mutators
void Registro::setFecha(Fecha sFecha){
    fecha = sFecha;
}

void Registro::setHora(Hora sHora){
    hora = sHora;
}

void Registro::setIpOrigen(string sIpOrigen){
    ipOrigen = sIpOrigen;
}

void Registro::setPuertoOrigen(string sPuertoOrigen){
    puertoOrigen = sPuertoOrigen;
}

void Registro::setNombreOrigen(string sNombreOrigen){
    nombreOrigen = sNombreOrigen;
}

void Registro::setIpDestino(string sIpDestino){
    ipDestino = sIpDestino;
}

void Registro::setPuertoDestino(int sPuertoDestino){
    puertoDestino = sPuertoDestino;
}

void Registro::setNombreDestino(string sNombreDestino){
    nombreDestino = sNombreDestino;
}
