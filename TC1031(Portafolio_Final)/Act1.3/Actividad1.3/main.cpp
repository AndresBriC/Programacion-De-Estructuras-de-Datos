//
//  main.cpp
//  Act 1.3
//
//  Created by inigo guerra on 21/09/20.
//  Copyright © 2020 inigo guerra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Registro.h"
#include "Ordenamiento.h"
#include "Fecha.h"

using namespace std;

//Función para encontrar si las computadoras pertenecen a alguien
bool duenosComputadoras(string nombre, int size, vector<Registro> lista){
    int encontrados = 0;
    for (int i = 0; i < size; ++i){
        if((lista[i].getNombreOrigen() == nombre) || (lista[i].getNombreDestino() == nombre)){
            encontrados++;
        }
    }
    if(encontrados > 0){
        return true;
    }
    else{
        return false;
    }
}

//Convierte un vector de caracteres a una string
string vectorToString(vector<char> vectToConv){
    string s(vectToConv.begin(), vectToConv.end());

    return s;
}

Fecha StringToFecha(string fechaATransformar){

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

//Codigo que se usa para responder las siete preguntas
void responderPreguntas(){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("equipo6.csv");
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
    int secondDayCounter = 0; //Usado para contar los registros del segundo dia

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

    //Variables para detectar cual es el primer, segunda y tercer fecha
    Fecha fechaMenor = listaRegistros[0].getFecha();
    Fecha fechaSegundaMenor(30, 12, 3000);

    //Ciclo para pasar por cada registro de la lista
    for(int i = 0; i < linecount; i++){

        //cout << "Fecha registro actual " << listaRegistros[i].getFecha() << compararFechas(listaRegistros[i].getFecha(), fechaMenor) << endl;

        //Compara la fecha del indice actual con la menor registrada para detectar la menor y segunda menor
        if(listaRegistros[i].getFecha() < fechaMenor){ //2 en funcion de comparar fecha indica que la fecha A es menor a la B
            fechaSegundaMenor = fechaMenor;
            fechaMenor = listaRegistros[i].getFecha();
        }

        if(listaRegistros[i].getFecha() > fechaMenor && listaRegistros[i].getFecha() < fechaSegundaMenor){ //2 en funcion de comparar fecha indica que la fecha A es menor a la B
            fechaSegundaMenor = listaRegistros[i].getFecha();
        }

        //Despliega la lista de registros
        //cout << listaRegistros[i] << endl;
    }

    //Pasa por cada registro y cuenta los que pertenecen a la segunda fecha
    for(int i = 0; i < linecount; i++){
        if(listaRegistros[i].getFecha() == fechaSegundaMenor){
            secondDayCounter++;
        }
    }


    //Datos del archivo
    cout << "Numero de registros: " << linecount << endl;
    cout << "Registros del segundo dia: " << secondDayCounter << endl;
    cout << "Primer dia: " << fechaMenor << " \nSegundo dia: " << fechaSegundaMenor << endl;

    cout << endl;

    //Asignar los nombres con .reto.com a un arreglo
    vector<string> nombres = {"jeffrey.reto.com", "bett.reto.com", "katherine.reto.com", "scott.reto.com", "benjamin.reto.com", "samuel.reto.com", "raymond.reto.com"};
    long int sizenombres = nombres.size();  //tamaño del vector de nombres
    long int sizenombre;
    int duenoencontrado = 0;
    cout << "Hay computadoras que pertenecen a: " << endl;
    for(int i = 0; i < sizenombres; i++){
        //revisa si aparece ese nombre en los registros
        if(duenosComputadoras(nombres[i], linecount, listaRegistros)){
            sizenombre = nombres[i].size();
            nombres[i].erase(sizenombre - 9);   //elimina el .reto.com
            cout << nombres[i] << endl;
            duenoencontrado++;
        }
    }
    if(duenoencontrado == 0){
        cout << "Ninguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond." << endl;
    }
    cout << endl;

    //Dirección interna de la compañía
    string ip;
    string encontrado = "-";
    int i = 0;
    while ((encontrado == "-") && (i < linecount)){
        ip = listaRegistros[i].getIpOrigen();
        if(((ip[0] == '1') && (ip[1] == '0')) || ((ip[0] == '1') && (ip[1] == '7') && (ip[2] == '2')) || ((ip[0] == '1') && (ip[1] == '9') && (ip[2] == '2'))){
            encontrado = ip;
        }
        i++;
    }
    cout << "La dirección de la red interna de la compañía es: " << encontrado << endl;
    cout << endl;

    //Buscar server.reto.com
    if(duenosComputadoras("server.reto.com", linecount, listaRegistros)){
        cout << "Alguna computadora se llama server.reto.com" << endl;
    }
    else{
        cout << "Ninguna computadora se llama server.reto.com" << endl;
    }
    cout << endl;


    //Buscar los servicions de correo electrónico
    vector<string> correos; //vector para almcenar las direcciones de correo
    int correosSize = 0; //Referencia al tamano del vector correos
    for(int i = 0; i < linecount; i++){
        if(listaRegistros[i].getNombreDestino() != "-"){
            int correoencontrado = 0;
            //Verificar si ya está en el vector ese servicio
            for(int j = 0; j < correosSize; ++j){
                if(listaRegistros[i].getNombreDestino() == correos[j]){
                    correoencontrado++;
                }
            }
            //Si todavía no está en el vector de correos agragrlo
            if(correoencontrado == 0){
                correos.push_back(listaRegistros[i].getNombreDestino());
                correosSize = correos.size();
            }
        }
    }
    cout << "Los servicios de correo electrónico usados son: " << endl;
    //Imprimir los correos encontrados
    for(int i = 0; i < correosSize; i++){
        cout << correos[i] << ", ";
    }
    cout << endl << endl;


    vector<int> puertos; //vector para almcenar los puertod destino
    int puertosSize = 0; //Referencia al tamano del vector correos
    for(int i = 0; i < linecount; i++){
        if(listaRegistros[i].getPuertoDestino() < 1000){
            int puertoencontrado = 0;
            //Verificar si ya está en el vector ese puerto
            for(int j = 0; j < puertosSize; ++j){
                if(listaRegistros[i].getPuertoDestino() == puertos[j]){
                    puertoencontrado++;
                }
            }
            //Si todavía no está en el vector de correos agragrlo
            if(puertoencontrado == 0){
                puertos.push_back(listaRegistros[i].getPuertoDestino());
                puertosSize = puertos.size();
            }
        }
    }

    cout << "Los puertos menores a 1000 usados son: " << endl;
    //Imprimir los correos encontrados
    for(int i = 0; i < puertosSize; i++){
        cout << puertos[i] << ", ";
    }
    cout << endl;

}


int main()
{
    responderPreguntas(); //Ejecuta todo el codigo que se usa para responder las 7 preguntas

    return 0;
}
