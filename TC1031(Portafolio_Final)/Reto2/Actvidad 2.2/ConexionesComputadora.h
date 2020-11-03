//
//  ConexionesComputadora.hpp
//  Act 2.2
//
//  Created by inigo guerra on 12/10/20.
//  Copyright © 2020 inigo guerra. All rights reserved.
//

#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#include "Registro.h"
#include "Fecha.h"

using namespace std;

class ConexionesComputadora{
private:
    string IP;
    string nombre;
    stack <Registro> conexionesEntrantes;
    queue <Registro> conexionesSalientes;
    //Chequeo de 3 consecutivas
    bool threeConsecutiveFound;
    int consecutiveCounter;
    string previousWebsite;
    string consecutiveWebsite;

public:
    //Constructores
    ConexionesComputadora();
    ConexionesComputadora(string, string);

    //Accesors
    string getIP();
    string getNombre();
    stack <Registro> getConexionesEntrantes();
    queue <Registro> getConexionesSalientes();
    string getConsecutiveWebsite();
    bool getThreeConsecutiveFound();

    //Mutators
    void setIP(string);
    void setNombre(string);

    //Métodos para leer y agregar datos a Conexiones Entrantes
    void llenarConexionesEntrantes(string);
    Registro ultimaConexionEntrante();
    long int tamanoConexionesEntrantes();

    //Métodos para leer y agregar datos a Conexiones Salientes
    void llenarConexionesSalientes(string);
    Registro primeraConexionSaliente();
    Registro ultimaConexionSaliente();
    long int tamanoConexionesSalientes();

    //Metodo para llenar conexiones salientes y entrantes
    void llenarAmbasConexiones(string);
    void threeConsecutiveCheck(string nombreDestino, int puertoDestino);

};

#endif /* ConexionesComputadora_hpp */
