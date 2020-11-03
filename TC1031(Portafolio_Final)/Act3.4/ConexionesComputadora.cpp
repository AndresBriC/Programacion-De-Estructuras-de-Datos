//
//  ConexionesComputadora.cpp
//  Act 2.2
//
//  Created by inigo guerra on 12/10/20.
//  Copyright © 2020 inigo guerra. All rights reserved.
//

#include "ConexionesComputadora.h"
#include <fstream>
#include <sstream>
#include <string>

//Constructores
ConexionesComputadora::ConexionesComputadora(){
    IP = "";
    nombre = "";

    //Para contar consecutivas del mismo sitio web
    threeConsecutiveFound = false;
    int consecutiveCounter = 0;
    string previousWebsite = "";
}

ConexionesComputadora::ConexionesComputadora(string ip, string n){
    IP = ip;
    nombre = n;
    llenarConexionesEntrantes(ip);
    llenarConexionesSalientes(ip);
    //Para contar consecutivas del mismo sitio web
    threeConsecutiveFound = false;
    int consecutiveCounter = 0;
    string previousWebsite = "";
}

//Accesors
string ConexionesComputadora::getIP(){
    return IP;
}

string ConexionesComputadora::getNombre(){
    return nombre;
}

stack <Registro> ConexionesComputadora::getConexionesEntrantes(){
    return conexionesEntrantes;
}

queue <Registro> ConexionesComputadora::getConexionesSalientes(){
    return conexionesSalientes;
}

string ConexionesComputadora::getConsecutiveWebsite(){
    return consecutiveWebsite;
}

bool ConexionesComputadora::getThreeConsecutiveFound(){
    return threeConsecutiveFound;
}

//Mutators
void ConexionesComputadora::setIP(string ip){
    IP = ip;
}

void ConexionesComputadora::setNombre(string n){
    nombre = n;
}

//Lee el archivo y pone las conexiones entrantes en una cola
void ConexionesComputadora::llenarConexionesEntrantes(string ip){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("equipo6.csv");
    string line;

    //Variables para almacenar los datos de cada registro
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
        //getline(ss, nombreDestino, ',');
        ss >> nombreDestino;

        fecha = fecha.stringToFecha(fechaString); //Convierte la fecha de formato string a objeto fecha
        hora = hora.stringToHora(horaString); //Convierte la hora de formato string a objeto hora

        //En las conexiones entrantes la dirección ip aparece como ip destino
        if (ipDestino == ip){
            //Agrega los registros al final de la queue
            conexionesEntrantes.push(Registro(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino));
            //std::cout << conexionesEntrantes.top() << std::endl; //Imprime las conexiones (Debug)

            //Si no ha encontrado 3 consecutivos, los busca
            if(!threeConsecutiveFound){
                threeConsecutiveCheck(nombreDestino, puertoDestino);
            }
        }
    }
}

//El ultimo elemnto en ser insertado a la queue
Registro ConexionesComputadora::ultimaConexionEntrante(){

    Registro registroVacio;

    if(conexionesEntrantes.size() == 0){
        return registroVacio;
    }
    else{
        return conexionesEntrantes.top();
    }
}

long int ConexionesComputadora::tamanoConexionesEntrantes(){
    return conexionesEntrantes.size();
}

//Lee el archivo y pone las conexiones entrantes en una cola
void ConexionesComputadora::llenarConexionesSalientes(string ip){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("equipo6.csv");
    string line;

    //Variables para almacenar los datos de cada registro
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
        //getline(ss, nombreDestino, ',');
        ss >> nombreDestino;

        fecha = fecha.stringToFecha(fechaString); //Convierte la fecha de formato string a objeto fecha
        hora = hora.stringToHora(horaString); //Convierte la hora de formato string a objeto hora

        //En las conexiones saliente la dirección ip aparece como ip fuente
        if (ipOrigen == ip){
            //Agrega los registros al final de la queue
            conexionesSalientes.push(Registro(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino));
            std::cout << conexionesSalientes.back() << std::endl; //Imprime las conexiones (Debug)

            //Si no ha encontrado 3 consecutivos, los busca
            if(!threeConsecutiveFound){
                threeConsecutiveCheck(nombreDestino, puertoDestino);
            }
        }
    }
}

//El primer elemnto en ser insertado en el stack
Registro ConexionesComputadora::primeraConexionSaliente(){

    Registro registroVacio;

    if(conexionesSalientes.size() == 0){
        return registroVacio;
    }
    else{
        return conexionesSalientes.front();
    }
}

//El ultimo elemento en ser insertado en el stack
Registro ConexionesComputadora::ultimaConexionSaliente(){

    Registro registroVacio;

    if(conexionesSalientes.size() == 0){
        return registroVacio;
    }
    else{
        return conexionesSalientes.back();
    }
}

long int ConexionesComputadora::tamanoConexionesSalientes(){
    return conexionesSalientes.size();
}

//Lee el archivo y pone las conexiones entrantes en una cola
void ConexionesComputadora::llenarAmbasConexiones(string ip){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("equipo6.csv");
    string line;

    //Variables para almacenar los datos de cada registro
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
        ss >> puertoDestino;
        //getline(ss, nombreDestino, ',');
        ss >> nombreDestino;

        fecha = fecha.stringToFecha(fechaString); //Convierte la fecha de formato string a objeto fecha
        hora = hora.stringToHora(horaString); //Convierte la hora de formato string a objeto hora

        //En las conexiones entrantes la dirección ip aparece como ip destino
        if (ipDestino == ip){
            //Agrega los registros al final de la queue
            conexionesEntrantes.push(Registro(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino));
            //std::cout << conexionesEntrantes.top() << std::endl; //Imprime las conexiones (Debug)

            //Si no ha encontrado 3 consecutivos, los busca
            if(!threeConsecutiveFound){
                threeConsecutiveCheck(nombreDestino, puertoDestino);
            }
        }

        //En las conexiones saliente la dirección ip aparece como ip fuente
        if (ipOrigen == ip){
            //Agrega los registros al final de la queue
            conexionesSalientes.push(Registro(fecha, hora, ipOrigen, puertoOrigen, nombreOrigen, ipDestino, puertoDestino, nombreDestino));
            //std::cout << conexionesSalientes.back() << std::endl; //Imprime las conexiones (Debug)

            //Si no ha encontrado 3 consecutivos, los busca
            if(!threeConsecutiveFound){
                threeConsecutiveCheck(nombreDestino, puertoDestino);
            }
        }
    }
}


void ConexionesComputadora::threeConsecutiveCheck(string nombreDestino, int puertoDestino){

    if((puertoDestino == 80 || puertoDestino == 443) && nombreDestino == previousWebsite){
        //std::cout << "Consecutive found" << std::endl;
        consecutiveCounter++;
        if(consecutiveCounter == 2){
            //std::cout << "3 consecutives found" << std::endl;
            threeConsecutiveFound = true;
            consecutiveWebsite = nombreDestino;
        }
    }
    else{
        consecutiveCounter = 0;
    }

    //Checa si son 3 seguidas del mismo sitio web
    if(puertoDestino == 80 || puertoDestino == 443){
        previousWebsite = nombreDestino;
        //std::cout << "Website found" << std::endl;
    }
}

