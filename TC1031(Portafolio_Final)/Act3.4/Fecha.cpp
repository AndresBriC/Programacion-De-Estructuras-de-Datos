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

//Convierte un vector de caracteres a una string
string Fecha::vectorToString(vector<char> vectToConv){
    string s(vectToConv.begin(), vectToConv.end());

    return s;
}

Fecha Fecha::stringToFecha(string fechaATransformar){

    //Almacena los tamanios del string de la fecha en un int
    int FechaSize = fechaATransformar.size();

    //Crea array de caracteres para la primera fecha y lo copia
    char charFecha[FechaSize + 1];
    fechaATransformar.copy(charFecha, FechaSize + 1);

    //Vectores para almacenar dia, mes y anio
    vector<char> diaTemp;
    vector<char> mesTemp;
    vector<char> anioTemp;

    //Ints para almacenar dias, meses y anios finales
    int dia = 0;
    int mes = 0;
    int anio = 0;

    //Variables usadas en el for para seaparar dia, mes y anio
    int contadorGuion = 0;//Para detectar cual guion se esta leyendo
    vector<char> contenedorFechas; //Para almacenar el dia/mes/anio temporalmente

    //Separa dia, mes y anio y las pone en vectores
    for(int i = 0; i < FechaSize; i++){

        //cout << charPrimeraFecha[i]; //Debug

        //Checa en que guion de la fecha va en el array
        if(charFecha[i] == '-'){
            contadorGuion++;
        }

        //Agrega la parte del dia a un vector
        if(charFecha[i] != '-' && contadorGuion == 0){
            diaTemp.push_back(charFecha[i]);
        }

        //Agrega la parte del mes a un vector
        if(charFecha[i] != '-' && contadorGuion == 1){
            mesTemp.push_back(charFecha[i]);
        }

        //Agrega la parte del anio a un vector
        if(charFecha[i] != '-' && contadorGuion == 2){
            anioTemp.push_back(charFecha[i]);
        }
    }

    string tempString; //Para almacenar los strings que se van a convertir a ints

    //Vector a integer
    tempString = vectorToString(diaTemp); //Dia
    dia = stoi(tempString);
    tempString = vectorToString(mesTemp); //Mes
    mes = stoi(vectorToString(mesTemp));
    tempString = vectorToString(anioTemp); //Anio
    anio = stoi(vectorToString(anioTemp));

    //Objeto de tipo fecha a regresar
    Fecha fechaToReturn(dia, mes, anio);

    return fechaToReturn;
}
