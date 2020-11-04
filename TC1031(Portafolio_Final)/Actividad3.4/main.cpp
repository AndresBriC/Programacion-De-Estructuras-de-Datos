//
//  main.cpp
//  Act_3.4
//
//  Created by inigo guerra on 03/11/20.
//

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include "Registro.hpp"
using namespace std;

//Convierte un vector de caracteres a una string
string vectorToString(vector<char> vectToConv){
    string s(vectToConv.begin(), vectToConv.end());

    return s;
}

Fecha StringToFecha(string fechaATransformar){

    //Almacena los tamanios del string de la fecha en un int
    long int FechaSize = fechaATransformar.size();

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

//Lectura archivo, regresa un vector con todos los registros
vector<Registro> lecturaArchivo(){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("/Users/inigo/Desktop/Semstre 3/Estructuras de datos/TC1031(Portafolio_FInal)/Act_3.4/Act_3.4/equipo6.csv");
    string line;

    //Vector que contiene todos los registros con sus datos almecenados en diferentes strings
    vector<Registro> listaRegistros;

    //Vatiables para almacenar los datos de cada registro
    string fechaString = "";
    Fecha fecha;
    string hora = "";
    string ipOrigen = "";
    string puertoOrigen = "";
    string nombreOrigen = "";
    string ipDestino = "";
    int puertoDestino = 0;
    string nombreDestino = "";

    //Para responeder las preguntas
    int linecount = 0; //Cuenta el numero de lineas (registros)

    //Lectura de cada lina del csv
    while(getline(archivo, line)){

        stringstream ss(line); //(Tomado del ejemplo del github del profe [Investigar como funciona])

        //Lectura antes de cada coma y alacenamiento temporal en variable para cada dato
        getline(ss, fechaString, ',');
        getline(ss, hora, ',');
        getline(ss, ipOrigen, ',');
        getline(ss, puertoOrigen, ',');
        getline(ss, nombreOrigen, ',');
        getline(ss, ipDestino, ',');
        //getline(ss, puertoDestino, ',');
        ss >> puertoDestino;
        ss >> nombreDestino;

        fecha = StringToFecha(fechaString); //Convierte la fecha de formato string a objeto fecha

        //Crea un nuevo objeto al final del vector con los datos leidos previamente
        listaRegistros.push_back(Registro(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino));

        linecount++; //Agrega 1 al contador por cada linea
    }

    return listaRegistros;
}

map<string, int> conexionesPorDia (Fecha fecha){
    vector<Registro> registrosFecha;

    vector<Registro> registros = lecturaArchivo();

    long int sizeR = registros.size();
    int i = 0;
    Fecha fechaT;

    //Agrega todos los registros con la fecha indicada y que no pertenezcan a "-" o a reto.com a un vector
    while ((i < sizeR) && !(fechaT > fecha)){
        fechaT = registros[i].getFecha();
        if ((registros[i].getFecha() == fecha) && (registros[i].getNombreDestino() != ",-") && (registros[i].getNombreDestino() != "reto.com")){
            registrosFecha.push_back(registros[i]);
        }
        i++;
    }

    int count = 0;
    string sitio;
    map<string, int> conexiones;

    //Se repite hasta que el vector esté vacío
    while (registrosFecha.size() != 0){
        count = 0;
        sitio = registrosFecha[0].getNombreDestino(); //Usa el primer registro como referencia
        for (int i = 0; i < registrosFecha.size(); i++){
            //Cuenta cuántas veces está ese sitio y elimina del vector cada registro de el sitio
            if (registrosFecha[i].getNombreDestino() == sitio){
                registrosFecha.erase(registrosFecha.begin() + i);
                count++;
            }
        }
        //Crea un par con el número de veces que se encuentra el sitio y el nombre del sitio
        pair<string, int> conexionesSitio(sitio, count);
        //Agrega el par al mapa
        conexiones.insert(conexionesSitio);
    }

    return conexiones;
}

int main(int argc, const char * argv[]) {
    Fecha fecha(10, 8, 2020);
    map<string, int> conexiones = conexionesPorDia(fecha);
    for (auto elem : conexiones) {
            cout << "Key: " << elem.first << ", Value: " << elem.second << endl;
        }
    return 0;
}
