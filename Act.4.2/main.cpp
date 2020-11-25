//
//  main.cpp
//  Act_4.2
//
//  Created by inigo guerra on 20/11/20.
//

#include <iostream>
#include "Graph.hpp"
#include "Registro.hpp"
#include <fstream>
#include <sstream>

using namespace std;

//Lectura archivo, regresa un vector con todos los registros
vector<Registro> lecturaArchivo(){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("/Users/inigo/Desktop/Semstre 3/Estructuras de datos/TC1031(Portafolio_FInal)/Act_4.2/Act_4.2/equipo6.csv");
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

//Lectura archivo, regresa un vector cada fecha unica
vector<Fecha> getEachUniqueDate(){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("/Users/inigo/Desktop/Semstre 3/Estructuras de datos/TC1031(Portafolio_FInal)/Act_4.2/Act_4.2/equipo6.csv");
    string line;

    //Vector que contiene todos los registros con sus datos almecenados en diferentes strings
    vector<Fecha> listaFechas;

    //Vatiables para almacenar los datos de cada registro
    string fechaString = "";
    Fecha fecha;

    //Lectura de cada lina del csv
    while(getline(archivo, line)){

        stringstream ss(line); //(Tomado del ejemplo del github del profe [Investigar como funciona])

        //Lectura antes de cada coma y alacenamiento temporal en variable para cada dato
        getline(ss, fechaString, ',');

        fecha = fecha.stringToFecha(fechaString); //Convierte la fecha de formato string a objeto fecha

        if(listaFechas.empty()){
            //Crea un nuevo objeto al final del vector con los datos leidos previamente
            listaFechas.push_back(fecha);
            //cout << fecha << endl; //Debug
        }
        else if(listaFechas.back() != fecha){
            //Crea un nuevo objeto al final del vector con los datos leidos previamente
            listaFechas.push_back(fecha);
            //cout << fecha << endl; //Debug
        }
    }

    return listaFechas;
}

//Regresa un grafo con las conexiones entre computadoras
Graph<string, Fecha> * grafoConexionesIP(vector<Registro> registros){
    
    Graph<string, Fecha> * conexionesIP = new Graph<string, Fecha>();
    //Se crean vectores auxiliares para gregar los IP como vértices al grafo
    vector<Registro> registrosSinUsar = registros;
    long int size = registrosSinUsar.size();
    string IPOrigen;
    string IPDestino;
    string IPOrigenT;
    string IPDestinoT;
    string IPinterna = "172.22.164.";
    long int sizeIP;
    
    //Elimina los registros sin IP Origen del vector auxiliar
    for (int i = 0; i < size; i++){
        if ((registrosSinUsar[i].getIpOrigen() == ",-") || (registrosSinUsar[i].getIpOrigen() == "-")){
            registrosSinUsar.erase(registrosSinUsar.begin() + i);
        }
    }
    
    
    //Crea y agreaga vertices para cada dirección IP
    for (int i = 0; i < size; i++){
        IPOrigen = registros[i].getIpOrigen();
        IPDestino = registros[i].getIpDestino();
        
        //Verifica si las ip son parte de la red interna
        IPOrigenT = IPOrigen;
        IPDestinoT = IPDestino;
        sizeIP = IPOrigenT.size();
        while (sizeIP > 11){
            IPOrigenT.pop_back();
            sizeIP = IPOrigenT.size();
        }
        sizeIP = IPDestinoT.size();
        while (sizeIP > 11){
            IPDestinoT.pop_back();
            sizeIP = IPDestinoT.size();
        }
        
        
        if (!(conexionesIP->findVertex(IPOrigen)) && (IPOrigenT == IPinterna)){
            conexionesIP->addVertex(new Vertex<string, Fecha>(IPOrigen));
        }
        if (!(conexionesIP->findVertex(IPDestino)) && (IPDestinoT == IPinterna)){
            conexionesIP->addVertex(new Vertex<string, Fecha>(IPDestino));
        }
    }
    
    //Agrega una arista por cada registro y con la fecha de información
    Fecha fechaConexion;
    for (int i = 0; i < registrosSinUsar.size(); i++){
        IPOrigen = registrosSinUsar[i].getIpOrigen();
        IPDestino = registrosSinUsar[i].getIpDestino();
        fechaConexion = registrosSinUsar[i].getFecha();
        
        IPOrigenT = IPOrigen;
        IPDestinoT = IPDestino;
        sizeIP = IPOrigenT.size();
        while (sizeIP > 11){
            IPOrigenT.pop_back();
            sizeIP = IPOrigenT.size();
        }
        sizeIP = IPDestinoT.size();
        while (sizeIP > 11){
            IPDestinoT.pop_back();
            sizeIP = IPDestinoT.size();
        }
        
        if ((IPOrigenT == IPinterna) && (IPDestinoT == IPinterna)){
            conexionesIP->addEdge(conexionesIP->getVertex(IPOrigen), conexionesIP->getVertex(IPDestino), fechaConexion);
        }
    }
    
    return conexionesIP;
}

//Revisa si una dirección ip es la que tiene más conexiones salientes
bool verticeConMasCOnexiones(Graph<string, Fecha> * conexionesIP, string IP){
    bool masConexiones = true;
    long int size = conexionesIP->nodes.size();
    long int conexiones = conexionesIP->getVertex(IP)->getNEdges();
    for (int i = 0; i < size; i++){
        if (conexionesIP->nodes[i]->getNEdges() > conexiones){
            masConexiones = false;
            break;
        }
    }
    
    return masConexiones;
}

//Regresa el numero de conexiones salientes de una IP en una fecha
int conexionesDesdeA(Graph<string, Fecha> * conexionesIP, string IP, Fecha dia){
    int conexionesDia = 0;
    Vertex<string, Fecha> * A = conexionesIP->getVertex(IP);
    long int size = A->edges.size();
    
    for(int i = 0; i < size; i++){
        if ((A->getEdge(i)->getInfo() == dia)){
            conexionesDia++;
        }
    }
    
    return conexionesDia;
}

//Regresa el numero de conexiones entrantes a una IP en una fecha
int conexionesHaciaA(Graph<string, Fecha> * conexionesIP, string IP, Fecha dia){
    int conexionesDia = 0;
    long int size = conexionesIP->nodes.size();
    Vertex<string, Fecha> * vertice;
    Vertex<string, Fecha> * A = conexionesIP->getVertex(IP);
    
    for(int i = 0; i < size; i++){
        vertice = conexionesIP->getVertex(i);
        for (int i = 0; i < vertice->edges.size(); i++){
            if ((vertice->getEdge(i)->getInfo() == dia) && (vertice->getEdge(i)->getTarget() == A)){
                conexionesDia++;
            }
        }
    }
    
    return conexionesDia;
}

//Imprime las conexiones hacia un vertice cada dia
void conexionesEntrantesPorDia(Graph<string, Fecha> * conexionesIP, string IP, vector<Fecha> dias){

    long int size = dias.size();
    
    cout << endl;
    cout << "----------" << endl;
    cout << endl;
    
    for (int i = 0; i < size; i++){
        cout << "Conexiones hacia A el " << dias[i] << ": " << conexionesHaciaA(conexionesIP, IP, dias[i]) << endl;
    }
    
}

//Imprime las conexiones desde un vertice cada dia
void conexionesSalientesPorDia(Graph<string, Fecha> * conexionesIP, string IP, vector<Fecha> dias){

    long int size = dias.size();
    
    cout << endl;
    cout << "----------" << endl;
    cout << endl;
    
    for (int i = 0; i < size; i++){
        cout << "Conexiones desde A el " << dias[i] << ": " << conexionesDesdeA(conexionesIP, IP, dias[i]) << endl;
    }
    
}

int main(int argc, const char * argv[]) {
    
    vector<Fecha> fechas = getEachUniqueDate();
    vector<Registro> registros = lecturaArchivo();
    Graph<string, Fecha> * conexionesIP = grafoConexionesIP(registros);
    
    string IP = "172.22.164.1";
    
    cout << "A: " << IP << endl;
    cout << endl;
    
    conexionesSalientesPorDia(conexionesIP, IP, fechas);
    
    if (verticeConMasCOnexiones(conexionesIP, IP)){
        cout << "A es el vertice con más conexiones salientes. " << endl;
    }
    else{
        cout << "A no es el vertice con más conexiones salientes. " << endl;
    }
    
    
    conexionesEntrantesPorDia(conexionesIP, IP, fechas);
    
    delete conexionesIP;
}
