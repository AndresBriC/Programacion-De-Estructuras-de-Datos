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

//Checa si las IP's encontradas en IPentrantes se conectaron con alguno de los sitios raros.
vector<Registro> checaConexionEntreIpYNombresRaros(vector<Registro> registros, set<string> IPentrantes, bool &siteWasFound){
    string nombre1 = ",ggex1ffe16fwzk3as5vd.net";
    string nombre2 = ",e1vrkur1pw73zlhg9asc.ru";
    int registrosSize = registros.size();
    vector<Registro> registrosQueSeConectan;
    //bool nombre1Found, nombre2Found = false; //Variables para debug

    for (auto elem: IPentrantes){ //Por cada elemento en el set de IP's encontradas
        cout << "Checando para IP " << elem << endl;
        for(int i = 0; i<registrosSize; i++){ //Itera por cada registro
            //Checa si la IP entrante en el registro actual es igual a la IP entrante en la lista de IP's encontrantes y si el sitio con el que conecta es uno de los raros
            if((registros[i].getIpOrigen() == elem && registros[i].getNombreDestino() == nombre1) || (registros[i].getIpOrigen() == elem && registros[i].getNombreDestino() == nombre2)){
                cout << "El IP " << elem << " se conectó con el sitio " << registros[i].getNombreDestino() << endl;
                siteWasFound = true;
                registrosQueSeConectan.push_back(registros[i]);
                break; //Rompe el for de registros para comparar con el IP encontrado siguiente
            }


            //Debug para probar el caso donde se conecten con sitios raros
//            if(registros[i].getNombreDestino() == nombre1 && !nombre1Found){
//                cout << "El IP " << registros[i].getIpOrigen() << " se conectó con el sitio " << registros[i].getNombreDestino() << endl;
//                registrosQueSeConectan.push_back(registros[i]);
//                nombre1Found = true;
//                siteWasFound = true;
//            }
//
//            if(registros[i].getNombreDestino() == nombre1 && !nombre2Found){
//                cout << "El IP " << registros[i].getIpOrigen() << " se conectó con el sitio " << registros[i].getNombreDestino() << endl;
//                registrosQueSeConectan.push_back(registros[i]);
//                nombre2Found = true;
//                siteWasFound = true;
//            }
        }
    }

    if(siteWasFound == false){
        cout << "Ninguna de las IP's se conecta con alguno de los nombres raros" << endl;
    }
    else{
        cout << "Alguna de las IP's se conecta con alguno de los nombres raros" << endl;
    }

    return registrosQueSeConectan;

}

void checaPrimeraConexionYProtocolo(Registro registroActual){
    cout << "Primera fecha de conexion con el sitio raro: " << registroActual.getFecha() << " IP: " << registroActual.getIpOrigen() << " ";

    switch(registroActual.getPuertoDestino()){
        case 22:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Secure Shell, secure logins, file transfers y port forwarding" << endl;
            break;
        case 23:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Telnet protocol, Comunicaciones de texto no encriptadas" << endl;
            break;
        case 53:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Domain Name System (DNS)" << endl;
            break;
        case 67:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Bootstrap Protocol y usado por Dynamic Host Configuration Protocol" << endl;
            break;
        case 68:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Bootstrap Protocol y usado por Dynamic Host Configuration Protocol" << endl;
            break;
        case 69:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Trivial File Transfer Protocol" << endl;
            break;
        case 70:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Gopher Protocol" << endl;
            break;
        case 80:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Hypertext Transfer Protocol" << endl;
            break;
        case 110:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Post Office Protocol, versión 3" << endl;
            break;
        case 135:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: DCE endpoint resolution, Microsoft EPMAP" << endl;
            break;
        case 443:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Hypertext Transfer Protocol" << endl;
            break;
        case 445:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Microsoft DS Active Directory, Microsoft DS SMB file sharing" << endl;
            break;
        case 465:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: URL Rendezevous Directory para SSM" << endl;
            break;
        case 666:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: para Doom, juego de disparos en primera persona" << endl;
            break;
        case 993:
            cout << "Protocolo: " << registroActual.getPuertoDestino() << " Uso: Internet Message Access Protocol en TLS/SSL" << endl;
            break;
    }
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

    //Pregunta 6
    bool conectionWasFound = false; //Almacena si se encontro una conexion con alguno de los sitios raros
    vector<Registro> registrosConectadosASitioRaro; //Vector que almacena los registros que se conectaron uno de los sitios raros

    cout << "Direcciones IP encontradas que se comunicaron con alguno de los dos sitios raros: " << endl;
    registrosConectadosASitioRaro = checaConexionEntreIpYNombresRaros(registros, IPentrantes, conectionWasFound);

    //Pregunta 7
    cout << endl;
    cout << "Pregunta 7" << endl;
    cout << endl;

    int registrosConectadosASitioRaroSize = registrosConectadosASitioRaro.size(); //Referencia al tamanio del vector

    if(conectionWasFound){ //Si se encontraron conexiones entre las IP y los sitios raros
        for(int i = 0; i<registrosConectadosASitioRaroSize; i++){
            checaPrimeraConexionYProtocolo(registrosConectadosASitioRaro[i]);
        }
    }
    else{ //Si no se encontraron conexiones entre las IP y los sitios raros
        cout << "Ninguna de las IP's encontradas se conecta con alguno de los sitios raros" << endl;
    }

}
