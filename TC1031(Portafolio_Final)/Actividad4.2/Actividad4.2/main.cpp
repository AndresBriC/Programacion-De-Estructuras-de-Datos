//
//  main.cpp
//  Act_4.2
//
//  Created by inigo guerra on 20/11/20.
//

#include <iostream>
#include "Graph.hpp"
#include "Registro.hpp"
#include <map>
#include <fstream>
#include <sstream>

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

//Lectura archivo, regresa un vector cada fecha unica
vector<Fecha> getEachUniqueDate(){
    //Para lectura del csv
    ifstream archivo;
    archivo.open("equipo6.csv");
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

//Crea un grafo de todas las conexiones del dia indicado
Graph<string, int>* creaGrafoConexionesASitiosEnDia(vector<Registro> registros, Fecha diaAChecar, string nombreAChecar){
    Graph<string, int> *grafoDelDia = new Graph<string, int>();
    Vertex<string, int> *base = new Vertex<string, int>("Base"); //Crea el vertice base

    grafoDelDia->addVertex(base); //Agrega el nodo base al grafo

    int registrosSize = registros.size(); //Tamanio del vector registros
    int finalIterator = (registros.size()) - 1;

    Vertex<string, int> *nuevo; //Vertice para agregar nuevas conexiones
    Vertex<string, int> *encontrado; //Vertice para sitios ya existentes
    Edge<string, int> *edgeEncontrada; //Arista para los vertices encontrados
    int newEdgeInfo = 0; //Info del edge actual


    //Itera por todos los registros
    for(int i = 0; i<registrosSize; i++){
        string nombreSitio = registros[i].getNombreDestino();

        //Si no esta el vertice en el grafo
        if(grafoDelDia->findVertex(nombreSitio) == false && registros[i].getFecha() == diaAChecar){
            //Crea un vertice con el sitio
            grafoDelDia->addVertex(nombreSitio);
            //cout << *grafoDelDia->getVertex(nombreSitio) << endl;
            //Crea una artista con valor 1 entre la base y el nuevo vertice
            //grafoDelDia->addEdge(base, grafoDelDia->getVertex(nombreSitio), 1);
            grafoDelDia->addEdge(grafoDelDia->getVertex(nombreSitio), base, 1);
        }

        //Si ya esta
        if(grafoDelDia->findVertex(nombreSitio) == true && registros[i].getFecha() == diaAChecar){
            //Agrega +1 al contador en la arista
            encontrado = grafoDelDia->getVertex(nombreSitio);
            //cout << "1" << endl;
            edgeEncontrada = encontrado->getEdge(0);
            //cout << "2" << endl;
            newEdgeInfo = edgeEncontrada->getInfo() + 1; //El valor del edge actual + 1
            //cout << "3" << endl;
            edgeEncontrada->setInfo(newEdgeInfo);
           //cout << "4" << endl;
        }

        //Si se llega al final de los registros sin encontrar el sitio
        if(grafoDelDia->findVertex(nombreAChecar) == false){
            //cout << "Se llego al final sin encontrarlo" << endl;
            grafoDelDia->addVertex(nombreAChecar);
            grafoDelDia->addEdge(grafoDelDia->getVertex(nombreAChecar), base, 0);
        }
    }

    //cout << *grafoDelDia << endl;

    return grafoDelDia;

    delete grafoDelDia;
}

//,e1vrkur1pw73zlhg9asc.ru y ,ggex1ffe16fwzk3as5vd.net
int conexionesANombrePorDia(string nombreAChecar, vector<Fecha> dias, vector<Registro> registros){
    long int size = dias.size();
    Graph<string, int> *grafoDelDia = new Graph<string, int>();

    cout << "Checando " << nombreAChecar << endl;
    cout << endl;

    //Itera por cada dia diferente
    for (int i = 0; i < size; i++){
        //Imprime las conexiones
        cout << "Fecha: " << dias[i] << endl;
        cout << endl;
        grafoDelDia = creaGrafoConexionesASitiosEnDia(registros, dias[i], nombreAChecar);
        //cout << *grafoDelDia << endl;
        cout << *grafoDelDia->getVertex(nombreAChecar);
    }



    delete grafoDelDia;
}


//,steamcommunity.com el 20-8-2020 tiene trafico anomalo


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

    cout << endl;
    cout << "Sitios con nombres raros identificados previamente: ,e1vrkur1pw73zlhg9asc.ru y ,ggex1ffe16fwzk3as5vd.net" << endl;
    cout << endl;
    conexionesANombrePorDia(",e1vrkur1pw73zlhg9asc.ru",fechas, registros);
    conexionesANombrePorDia(",ggex1ffe16fwzk3as5vd.net",fechas, registros);

    cout << endl;
    cout << "Sitio y dia de trafico anómalo encontrado previamente: ,steamcommunity.com el 20-8-2020" << endl;
    conexionesANombrePorDia(",steamcommunity.com",fechas, registros);

    delete conexionesIP;

    return 0;
}
