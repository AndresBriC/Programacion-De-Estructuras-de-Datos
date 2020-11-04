//
//  Hora.cpp
//  Act_3.4
//
//  Created by inigo guerra on 03/11/20.
//

#include <iostream>

#include "Hora.hpp"

using namespace std;

//Constructores
Hora::Hora(){
    hora = 0;
    minuto = 0;
    segundo = 0;
}

Hora::Hora(int cHora, int cMinuto, int cSegundo){
    hora = cHora;
    minuto = cMinuto;
    segundo = cSegundo;
}

//Sobrecarga de operadores
ostream & operator<<(ostream & os, const Hora & hora){
    os << hora.hora << ":";
    os << hora.minuto << ":";
    os << hora.segundo;

    return os;
}

bool operator== (const Hora &h1, const Hora &h2){
    return h1.segundo == h2.segundo && h1.minuto == h2.minuto && h1.hora == h2.hora;
}

bool operator!= (const Hora &h1, const Hora &h2){
    return !(h1 == h2);
}

bool operator> (const Hora &h1, const Hora &h2){
    return h1.hora > h2.hora || (h1.hora == h2.hora && h1.minuto > h2.minuto) || (h1.hora == h2.hora && h1.minuto == h2.minuto && h1.segundo > h2.segundo);
}

bool operator< (const Hora &h1, const Hora &h2){
    return h1.hora < h2.hora || (h1.hora == h2.hora && h1.minuto < h2.minuto) || (h1.hora == h2.hora && h1.minuto == h2.minuto && h1.segundo < h2.segundo);
}

//Accessors
int Hora::getSegundo(){
    return segundo;
}

int Hora::getMinuto(){
    return minuto;
}

int Hora::getHora(){
    return hora;
}

//Mutators
void Hora::setSegundo(int mSegundo){
    segundo = mSegundo;
}

void Hora::setMinuto(int mMinuto){
    minuto = mMinuto;
}

void Hora::setHora(int mHora){
    hora = mHora;
}

//Convierte un vector de caracteres a una string
string Hora::vectorToString(vector<char> vectToConv){
    string s(vectToConv.begin(), vectToConv.end());

    return s;
}

Hora Hora::stringToHora(string horaATransformar){

    //Almacena los tamanios del string de la hora en un int
    int horaSize = horaATransformar.size();

    //Crea array de caracteres para la primera hora y lo copia
    char charHora[horaSize + 1];
    horaATransformar.copy(charHora, horaSize + 1);

    //Vectores para almacenar segundo, minuto y hora
    vector<char> segundoTemp;
    vector<char> minutoTemp;
    vector<char> horaTemp;

    //Ints para almacenar segundos, minutoes y horas finales
    int segundo = 0;
    int minuto = 0;
    int hora = 0;

    //Variables usadas en el for para seaparar segundo, minuto y hora
    int contadorDosPuntos = 0;//Para detectar cual dos puntos se esta leyendo
    vector<char> contenedorHoras; //Para almacenar el segundo/minuto/hora temporalmente

    //Separa segundo, minuto y hora y las pone en vectores
    for(int i = 0; i < horaSize; i++){

        //cout << charHora[i]; //Debug

        //Checa en que dos puntos de la hora va en el array
        if(charHora[i] == ':'){
            contadorDosPuntos++;
        }

        //Agrega la parte del segundo a un vector
        if(charHora[i] != ':' && contadorDosPuntos == 0){
            horaTemp.push_back(charHora[i]);
        }

        //Agrega la parte del minuto a un vector
        if(charHora[i] != ':' && contadorDosPuntos == 1){
            minutoTemp.push_back(charHora[i]);
        }

        //Agrega la parte del hora a un vector
        if(charHora[i] != ':' && contadorDosPuntos == 2){
            segundoTemp.push_back(charHora[i]);
        }
    }

    string tempString; //Para almacenar los strings que se van a convertir a ints

    //Vector a integer
    tempString = vectorToString(horaTemp); //Hora
    hora = stoi(vectorToString(horaTemp));
    tempString = vectorToString(minutoTemp); //Minuto
    minuto = stoi(vectorToString(minutoTemp));
    tempString = vectorToString(segundoTemp); //Segundo
    segundo = stoi(tempString);

    //Objeto de tipo hora a regresar
    Hora horaToReturn(hora, minuto, segundo);

    //cout << horaToReturn << endl; //Debug

    return horaToReturn;
}
