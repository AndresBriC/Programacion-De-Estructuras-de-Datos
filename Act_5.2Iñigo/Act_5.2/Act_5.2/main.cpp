//
//  main.cpp
//  Act_5.2
//
//  Created by inigo guerra on 24/11/20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>


#include "ConexionesComputadora.hpp"

using namespace std;

bool perteneceAReto(string nombre){
    bool pertenece = false;
    string reto = ".reto.com";
    long int size = nombre.size();
    
    while (size > 9){
        nombre.erase(nombre.begin());
        size = nombre.size();
    }
    
    if (nombre == reto){
        pertenece = true;
    }
    
    return pertenece;
}

//Lectura archivo, regresa un vector con todos los registros
vector<Registro> lecturaArchivo(){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("/Users/inigo/Desktop/Semstre 3/Estructuras de datos/TC1031(Portafolio_FInal)/Act_5.2/Act_5.2/equipo6.csv");
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

//Crea un conjunto con todos los nombres
set<string> conjunto(vector<Registro> registros){
    set<string> nombres;
    string nombreOrigen;
    string nombreDestino;
    long int size = registros.size();
    string reto = ".reto.com";
    
    for (int i = 0; i < size; i++){
        nombreOrigen = registros[i].getNombreOrigen();
        nombreDestino = registros[i].getNombreDestino();
        
        //Agrega al conjunto si no pertenecen a .reto.com
        if (!perteneceAReto(nombreOrigen)){
            nombreOrigen = registros[i].getNombreOrigen();
            nombres.insert(nombreOrigen);
        }
        
        if (!perteneceAReto(nombreDestino)){
            nombreDestino = registros[i].getNombreDestino();
            nombres.insert(nombreDestino);
        }
        
    }
    
    return nombres;
}

//Genera un diccionario con cada IP y sus conexionesComputadoras
map<string, ConexionesComputadora> diccionario(vector<Registro> registros){
    map<string, ConexionesComputadora> diccionario;
    string IPorigen;
    string nombreOrigen;
    string IPdestino;
    string nombreDestino;
    ConexionesComputadora conexiones;
    long int size = registros.size();
    map<string, ConexionesComputadora>::iterator it;
    
    for (int i = 0; i < size; i++){
        IPorigen = registros[i].getIpOrigen();
        nombreOrigen = registros[i].getNombreOrigen();
        IPdestino = registros[i].getIpDestino();
        nombreDestino = registros[i].getNombreDestino();
        
        it = diccionario.lower_bound(IPorigen);
        if (it == diccionario.end()){
            conexiones.setIP(IPorigen);
            conexiones.setNombre(nombreOrigen);
            conexiones.llenarAmbasConexiones(IPorigen);
            diccionario[IPorigen] = ConexionesComputadora(conexiones);
        }
        
        it = diccionario.lower_bound(IPdestino);
        if (it == diccionario.end()){
            conexiones.setIP(IPdestino);
            conexiones.setNombre(nombreDestino);
            conexiones.llenarAmbasConexiones(IPdestino);
            diccionario[IPdestino] = ConexionesComputadora(conexiones);
        }
        
    }
    
    
    return diccionario;
}

//Regresa un mapa con el nombre anomalo y su IP
map<string, string> IPnombresAnomalos(vector<Registro> registros){
    map<string, string> IP;
    long int size = registros.size();
    string nombre1 = ",ggex1ffe16fwzk3as5vd.net";
    string nombre2 = ",e1vrkur1pw73zlhg9asc.ru";
    map<string, string>::iterator it;
    
    for (int i = 0; i < size; i++){
        if ((registros[i].getNombreOrigen() == nombre1)){
            it = IP.lower_bound(nombre1);
            if (it == IP.end()){
                IP[nombre1] = registros[i].getIpOrigen();
            }
        }
        if ((registros[i].getNombreOrigen() == nombre2)){
            it = IP.lower_bound(nombre2);
            if (it == IP.end()){
                IP[nombre2] = registros[i].getIpOrigen();
            }
        }
        if ((registros[i].getNombreDestino() == nombre1)){
            it = IP.lower_bound(nombre1);
            if (it == IP.end()){
                IP[nombre1] = registros[i].getIpDestino();
            }
        }
        if ((registros[i].getNombreDestino() == nombre2)){
            it = IP.lower_bound(nombre2);
            if (it == IP.end()){
                IP[nombre2] = registros[i].getIpDestino();
            }
        }
    }
    
    return IP;
}

//Regresa el numero de IPs con por lo menos una conexión entrante
int computadorasReto(vector<Registro> registros){
    int numComputadoras = 0;
    long int size = registros.size();
    string nombreOrigen;
    string nombreDestino;
    string reto = ".reto.com";
    set<string> IPreto;
    ConexionesComputadora conexiones;
    
    for (int i = 0; i < size; i++){
        nombreOrigen = registros[i].getNombreOrigen();
        nombreDestino = registros[i].getNombreDestino();
        
        //Agrega al conjunto si pertenecen a .reto.com
        if (perteneceAReto(nombreOrigen)){
            nombreOrigen = registros[i].getNombreOrigen();
            IPreto.insert(registros[i].getIpOrigen());
        }
        
        if (perteneceAReto(nombreDestino)){
            nombreDestino = registros[i].getNombreDestino();
            IPreto.insert(registros[i].getIpDestino());
        }
    }
    
    for(auto i: IPreto){
        conexiones.llenarConexionesEntrantes(i);
        if (conexiones.tamanoConexionesEntrantes() > 0){
            numComputadoras++;
        }
    }
    
    return numComputadoras;
}

//Regresa tods las IPs que tienen conexiones entrantes hacia las 5 computadoras elegidas
set<string> IPentrnates(vector<Registro> registros){
    set<string> IPs;
    set<string> seleccionadas {"171.19.102.131", "178.133.143.25", "195.255.183.229", "60.65.196.100", "15.178.77.225"};
    long int size = seleccionadas.size();
    stack<Registro> conexionesEntrantes;
    ConexionesComputadora conexiones;
    
    
    for (auto i: seleccionadas){
        conexiones.llenarConexionesEntrantes(i);
        size = conexiones.tamanoConexionesEntrantes();
        conexionesEntrantes = conexiones.getConexionesEntrantes();
        for (int j = 0; j < size; j++){
            IPs.insert(conexionesEntrantes.top().getIpOrigen());
            conexionesEntrantes.pop();
        }
    }
    
    
    
    return IPs;
}

int main(int argc, const char * argv[]) {
    
    vector<Registro> registros = lecturaArchivo();
    
    set<string> nombres = conjunto(registros);
    
    map<string, ConexionesComputadora> conexiones = diccionario(registros);
    
    map<string, string> IPanomalos = IPnombresAnomalos(registros);
    
    cout << endl;
    cout << "Nombres anomalos: " << endl; //Pregunta 1 y 2
    for (auto elem: IPanomalos){
        cout << "Nombre: " << elem.first << ", IP: " << elem.second << endl;
    }
    cout << endl;
    
    int numIPreto = computadorasReto(registros);
    
    //Pregunta 3 (se tarda mucho en correr esta parte)
    cout << "El número de IPs pertenecientes a reto.com con al menos una conexión entrante es: " << numIPreto << endl;
    cout << endl;
    
    set<string> IPentrantes = IPentrnates(registros);
    
    //Pregunta 4
    cout << "IPs de conexiones entrantes a 5 computadora seleccionadas" << endl;
    for (auto elem: IPentrantes){
        cout << elem << endl;
    }
    cout << endl;
    
    
    
}
