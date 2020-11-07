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
#include <utility>

#include "Registro.hpp"
#include "BST.h"

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

map<string, int> conexionesPorDia (Fecha fecha){
    vector<Registro> registrosFecha;

    vector<Registro> registros = lecturaArchivo();

    long int sizeR = registros.size();
    int i = 0;
    Fecha fechaT;

    //Agrega todos los registros con la fecha indicada y que no pertenezcan a "-" o a reto.com a un vector
    while ((i < sizeR) && !(fechaT > fecha)){
        fechaT = registros[i].getFecha();
        if ((registros[i].getFecha() == fecha) && (registros[i].getNombreDestino() != ",-") && (registros[i].getNombreDestino() != ",reto.com") && (registros[i].getNombreDestino() != ",server.reto.com") ){
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

//Ordena el mapa dado de forma descendiente. Tomado de: https://www.techiedelight.com/sort-map-values-cpp
//Convierte el mapa<K,V> a un multimapa<V,K>
template<typename K, typename V>
multimap<V,K, greater <int> > invertMap(map<K,V> const &map){ //El greater <int> asegura que se ordene en orden descendiente

    multimap<V,K, greater <int> > mMultimap;

    for(auto const &pair : map){
        mMultimap.insert(make_pair(pair.second, pair.first)); //Usando los valores del mapa dado, inserta los valores de manera invertida, para que ser vayan ordenando descendientemente
    }

    return mMultimap;
}

multimap<int, string, greater<int>> top(int n, Fecha myFecha){

    map<string, int> conexiones = conexionesPorDia(myFecha); //Obtiene la lista de conexiones del dia indicado
    multimap<int, string, greater <int> > testMultimap = invertMap(conexiones); //Obtiene la lista ordenada descendientemente de las conexiones del dia
    multimap<int, string, greater<int>> top5Map;

    int counter = 0;

    for (auto const &pair : testMultimap){ //Por cada par en el multimap
        if(counter < n){
            cout << pair.second << "," << pair.first << endl; //Imprime el sitio y luego el numero de conexiones
            top5Map.insert(make_pair(pair.first, pair.second));
            counter++;
        }
        else{
            break;
        }
    }

    return top5Map;
}

void sitiosConMuchoTrafico(int n, Fecha myFecha){

    map<string, int> conexiones = conexionesPorDia(myFecha); //Obtiene la lista de conexiones del dia indicado
    multimap<int, string, greater <int> > testMultimap = invertMap(conexiones); //Obtiene la lista ordenada descendientemente de las conexiones del dia

    int counter = 0;

    for (auto const &pair : testMultimap){ //Por cada par en el multimap
        if(counter < n && pair.first >= 100){
            cout << pair.second << ", " << pair.first << endl; //Imprime el sitio y luego el numero de conexiones
            counter++;
        }
        else{
            break;
        }
    }
}

void topBST(int n, Fecha myFecha){

    map<string, int> conexiones = conexionesPorDia(myFecha); //Obtiene la lista de conexiones del dia indicado
    BST<string> arbolConexiones;
    string key;
    int value;

    for(auto elem : conexiones){
        key = elem.first;
        value = elem.second;
        arbolConexiones.insertPair(key, value);
    }

    arbolConexiones.visitTopN(n);
}


int main(int argc, const char * argv[]) {
//    Fecha fecha(10, 8, 2020);
//    map<string, int> conexiones = conexionesPorDia(fecha);

//    Despliegue del conteo total del día
//    for (auto elem : conexiones) {
//            cout << "Key: " << elem.first << ", Value: " << elem.second << endl;
//    }

//    //Prueba top
//    int primerosN, topDia, topMes, topAnio;
//
//    cout << "Cuantos sitios de los sitios mas accesados en orden deseas ver? ";
//    cin >> primerosN;
//    cout << "De que dia? ";
//    cin >> topDia;
//    cout << "De que mes? ";
//    cin >> topMes;
//    cout << "De que anio? ";
//    cin >> topAnio;
//    cout << endl;
//    Fecha topFecha(topDia, topMes, topAnio);
//
//    top(primerosN, topFecha);

    vector<Fecha> uniqueDateVector = getEachUniqueDate();
    Fecha currentDate;
//
    int uniqueDateVectorSize = uniqueDateVector.size(); //Vector que contiene cada sitio que sale en el top 5, contando repetidos

    multimap<int, string, greater<int>> top5Map;
    vector< pair<int, string> > repetitionCounter;
    vector<string> top5SubsecuenteTemp;
    vector<string> top5Subsecuente;
    bool firstFiveCheck = false;

    //Top 5 de cada dia

    cout << "TOP 5 CADA DIA" << endl;

    for(int i = 0; i < uniqueDateVectorSize; i++){
        cout << endl;
        currentDate = uniqueDateVector[i];
        cout << currentDate << endl;
        top5Map = top(5, currentDate); //Pone los top 5 en un multimapa

        for(auto const &pair : top5Map){ //Pone los 5 del multimapa en un vector que contiene todos los top 5 con repetidos
            if(firstFiveCheck == false){
                top5Subsecuente.push_back(pair.second);
                top5SubsecuenteTemp.push_back(pair.second);
                firstFiveCheck == true;
            }
            else{
                top5SubsecuenteTemp.push_back(pair.second);
            }
            repetitionCounter.push_back(make_pair(pair.first, pair.second));
        }

        for(int j = 0; j < top5Subsecuente.size(); j++){
            for(int k = 0; k < top5SubsecuenteTemp.size(); k++){
                if(top5SubsecuenteTemp[k] == top5Subsecuente[j]){
                    break;
                }
                if(k == top5SubsecuenteTemp.size() && top5SubsecuenteTemp[k] != top5Subsecuente[j]){
                    top5Subsecuente.erase(top5Subsecuente.begin() + j);
                }
            }
        }
    }


    //Chequeo del sitios en el top 5 todos los días
    vector <pair<string, int> > uniqueNameCounter; //Vector de repeticiones por sitio
    uniqueNameCounter.push_back(make_pair(repetitionCounter[0].second, 0));

    cout << endl;
    for(int i = 0; i < repetitionCounter.size(); i++){
        for(int j = 0; j < uniqueNameCounter.size(); j++){
            if(uniqueNameCounter[j].first == repetitionCounter[i].second){ //Si el nombre ya esta en las dos listas
                uniqueNameCounter[j].second++; //Le suma 1 al contador de repeticiones
                break;
                //cout << "Encontrado en la lista" uniqueNameCounter[j].first<< ", " << uniqueNameCounter[j].second<< endl;
            }

            if(j == uniqueNameCounter.size() - 1 && uniqueNameCounter[j].first != repetitionCounter[i].second){ //Si ya se llega al final y no coincide el nombre del sitio en las dos listas
                uniqueNameCounter.push_back(make_pair(repetitionCounter[i].second, 1)); //Agrega el primer sitio web y pone su conteo de repeticion en 1
                break;
                //cout << "Encontrado por primera vez " << uniqueNameCounter[j].first<< ", " << uniqueNameCounter[j].second<< endl;
            }
        }
    }

    for(int i = 0; i < uniqueNameCounter.size(); i++){
        //cout << uniqueNameCounter[i].first << ", " << uniqueNameCounter[i].second << endl;
        if(uniqueNameCounter[i].second == uniqueDateVector.size()){
            cout << uniqueNameCounter[i].first << " se repite todos los dias." << endl;
        }
    }

//    //Top 5 de cada dia usando un BST
//    for(int i = 0; i < uniqueDateVectorSize; i++){
//        currentDate = uniqueDateVector[i];
//        cout << endl;
//        cout << currentDate << endl;
//        topBST(5, currentDate);
//    }

    //Sitio von una con una cantidad mas trafico que lo normal
    cout << "Los sitios con una cantidad mas alta de lo normal son: " << endl;
    cout << endl;
    for(int i = 0; i < uniqueDateVectorSize; i++){
        currentDate = uniqueDateVector[i];
        cout << endl;
        cout << currentDate << endl;
        sitiosConMuchoTrafico(5, currentDate);
    }

    return 0;
}
