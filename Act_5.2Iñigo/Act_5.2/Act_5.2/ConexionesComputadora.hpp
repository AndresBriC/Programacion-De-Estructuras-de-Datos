//
//  ConexionesComputadora.hpp
//  Act_5.2
//
//  Created by inigo guerra on 24/11/20.
//

#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#include "Registro.hpp"
#include "Fecha.hpp"

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

    //MÈtodos para leer y agregar datos a Conexiones Entrantes
    void llenarConexionesEntrantes(string);
    Registro ultimaConexionEntrante();
    long int tamanoConexionesEntrantes();

    //MÈtodos para leer y agregar datos a Conexiones Salientes
    void llenarConexionesSalientes(string);
    Registro primeraConexionSaliente();
    Registro ultimaConexionSaliente();
    long int tamanoConexionesSalientes();

    //Metodo para llenar conexiones salientes y entrantes
    void llenarAmbasConexiones(string);
    void threeConsecutiveCheck(string nombreDestino, int puertoDestino);

};

#endif /* ConexionesComputadora_hpp */
