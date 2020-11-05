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

//Lectura archivo, regresa un vector con todos los registros
vector<Registro> lecturaArchivo(){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("equipo6.csv");
    string line;

    //Vector que contiene todos los registros con sus datos almecenados en diferentes strings
    vector<Registro> listaRegistros;

    //Vatiables para almacenar los datos de cada registro
    string fechaString = "";
    string horaString = "";
    Fecha fecha;
    Hora hora;
    string ipOrigen = "";
    string puertoOrigen = "";
    string nombreOrigen = "";
    string ipDestino = "";
    int puertoDestino = 0;
    string nombreDestino = "";

    //Lectura de cada lina del csv
    while(getline(archivo, line)){

        stringstream ss(line); //(Tomado del ejemplo del github del profe [Investigar como funciona])

        //Lectura antes de cada coma y alacenamiento temporal en variable para cada dato
        getline(ss, fechaString, ',');
        getline(ss, horaString, ',');
        getline(ss, ipOrigen, ',');
        getline(ss, puertoOrigen, ',');
        getline(ss, nombreOrigen, ',');
        getline(ss, ipDestino, ',');
        //getline(ss, puertoDestino, ',');
        ss >> puertoDestino;
        ss >> nombreDestino;

        fecha = fecha.stringToFecha(fechaString); //Convierte la fecha de formato string a objeto fecha
        hora = hora.stringToHora(horaString); //Convierte la hora de formato string a objeto hora

        //Crea un nuevo objeto al final del vector con los datos leidos previamente
        listaRegistros.push_back(Registro(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino));
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
    int registrosFechaSize = registrosFecha.size();

    //Se repite hasta que el vector esté vacío
    while (registrosFecha.size() != 0){
        count = 0;
        sitio = registrosFecha[0].getNombreDestino(); //Usa el primer registro como referencia
        for (int i = 0; i < registrosFechaSize; i++){
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
