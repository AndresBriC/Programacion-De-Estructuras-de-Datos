//
//  main.cpp
//  Act 2.2
//
//  Created by inigo guerra on 12/10/20.
//  Copyright © 2020 inigo guerra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "ConexionesComputadora.h"

//Puertos 80 y 443 para sitios web

//Funcion que toma un numero entre 1 y 150 para generar la IP interna en base a la direccion de red obtenida en la actividad 1.3
string generaIpInterna(){

    int numParaIp; //Para generar IP segun la direccion de red
    string ipInterna = "172.22.164."; //Inicializada como la direccion de red encontrada en la primera parte del reto

    //Pide el numero entre 1 y 150
    do{
        std::cout << "Indique el numero entre 1 y 150 para generar IP interna segun direccion de red: ";
        std::cin >> numParaIp;
    }while(numParaIp < 1 || numParaIp > 150);

    int lenNumParaIp = to_string(numParaIp).length(); //Para agregar el numero dado al final de la direccion de red

    ipInterna.replace(11, lenNumParaIp, to_string(numParaIp)); //Agrega el numero indicado a la direccion de red para generar la IP interna

    return ipInterna;
}

void respondePreguntas(){

    string direccionDeRed = "172.22.164.";

    string ipInterna = generaIpInterna(); //Almacena la IP interna generada por la funcion
    ConexionesComputadora conexionesEncontradas;

    conexionesEncontradas.setNombre("Computadora 1");
    conexionesEncontradas.setIP(ipInterna);

    std::cout << "\nNombre computadora: " << conexionesEncontradas.getNombre() << endl;
    std::cout << "IP interna: " << conexionesEncontradas.getIP() << endl;

    conexionesEncontradas.llenarAmbasConexiones(ipInterna);
    std::cout << "\nTamanio conexiones entrantes: " << conexionesEncontradas.tamanoConexionesEntrantes() << std::endl;
    std::cout << "Ultima conexion entrante: " << conexionesEncontradas.ultimaConexionEntrante() << std::endl;

    std::cout << "\nTamanio conexiones salientes: " << conexionesEncontradas.tamanoConexionesSalientes() << std::endl;
    std::cout << "Primera conexion saliente: " << conexionesEncontradas.primeraConexionSaliente() << std::endl;
    std::cout << "Ultima conexion saliente: " << conexionesEncontradas.ultimaConexionSaliente() << std::endl;

    if(conexionesEncontradas.ultimaConexionEntrante().getFecha() > conexionesEncontradas.ultimaConexionSaliente().getFecha()){ //Entrante > Saliente
        std::cout << "\nLa ultima conexion recibida es entrante." << std::endl;
            if(direccionDeRed == conexionesEncontradas.ultimaConexionEntrante().getIpOrigen().substr(0,11) ){
                std::cout << "\nLa ultima conexion recibida es interna." << std::endl;
            }
            else{
                std::cout << "\nLa ultima conexion recibida es externa." << std::endl;
            }
    }
    else if(conexionesEncontradas.ultimaConexionEntrante().getFecha() < conexionesEncontradas.ultimaConexionSaliente().getFecha()){ //Entrante < Saliente
        std::cout << "\nLa ultima conexion recibida es saliente." << std::endl;
            if(direccionDeRed == conexionesEncontradas.ultimaConexionEntrante().getIpDestino().substr(0,11) ){
                std::cout << "\nLa ultima conexion recibida es interna." << std::endl;
            }
            else{
                std::cout << "\nLa ultima conexion recibida es externa." << std::endl;
            }
    }
    else{ //Dia Entrante = Saliente, checar hora
        if(conexionesEncontradas.ultimaConexionEntrante().getHora() > conexionesEncontradas.ultimaConexionSaliente().getHora()){ //Entrante > Saliente
            std::cout << "\nLa ultima conexion recibida es entrante." << std::endl;
            if(direccionDeRed == conexionesEncontradas.ultimaConexionEntrante().getIpOrigen().substr(0,11) ){
                std::cout << "\nLa ultima conexion recibida es interna." << std::endl;
            }
            else{
                std::cout << "\nLa ultima conexion recibida es externa." << std::endl;
            }
        }
        else if(conexionesEncontradas.ultimaConexionEntrante().getHora() < conexionesEncontradas.ultimaConexionSaliente().getHora()){ //Entrante < Saliente
            std::cout << "\nLa ultima conexion recibida es saliente." << std::endl;
            if(direccionDeRed == conexionesEncontradas.ultimaConexionEntrante().getIpDestino().substr(0,11) ){
                std::cout << "\nLa ultima conexion recibida es interna." << std::endl;
            }
            else{
                std::cout << "\nLa ultima conexion recibida es externa." << std::endl;
            }
        }
        else{
            std::cout << "\nLas conexiones entrante y saliente vienen del mismo instante." << std::endl;
        }
    }

    if(conexionesEncontradas.getThreeConsecutiveFound()){
        std::cout << "\nSe encontraron 3 conexiones consecutivas de un mismo sitio web" << std::endl;
        std::cout << "Sitio consecutivo " << conexionesEncontradas.getConsecutiveWebsite() << std::endl;
    }
    else{
        std::cout << "\nNo se encontraron 3 conexiones consecutivas de un mismo sitio web" << std::endl;
    }

}

int main(int argc, const char * argv[]) {
    respondePreguntas();

    return 0;
}
