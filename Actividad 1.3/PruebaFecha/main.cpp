#include <iostream>
#include <string>
#include <vector>

using namespace std;


//Convierte un vector de caracteres a una string
string vectorToString(vector<char> vectToConv){
    string s(vectToConv.begin(), vectToConv.end());

    return s;
}

//1 es Mayor, 2 es Menor, 3 es igual
int compararFechas(string primeraFecha, string segundaFecha){

    if(primeraFecha == segundaFecha){
        return 3;
    }

    //Almacena los tamanios del string de las fechas en ints
    int primeraFechaSize = primeraFecha.size();
    int segundaFechaSize = segundaFecha.size();

    //Crea array de caracteres para la primera fecha y lo copia
    char charPrimeraFecha[primeraFechaSize + 1];
    primeraFecha.copy(charPrimeraFecha, primeraFechaSize + 1);

    //Crea array de caracteres para la segunda fecha y lo copia
    char charSegundaFecha[segundaFechaSize + 1];
    segundaFecha.copy(charSegundaFecha, segundaFechaSize + 1);

    //Vectores para almacenar dia, mes y anio
    vector<char> diaTemp;
    vector<char> mesTemp;
    vector<char> anioTemp;

    //Ints para almacenar dias, meses y anios finales
    int diaPrimero = 0;
    int mesPrimero = 0;
    int anioPrimero = 0;
    int diaSegundo = 0;
    int mesSegundo = 0;
    int anioSegundo = 0;

    //Variables usadas en el for para seaparar dia, mes y anio
    int contadorGuion = 0;//Para detectar cual guion se esta leyendo
    vector<char> contenedorFechas; //Para almacenar el dia/mes/anio temporalmente

    //Separacion primera fecha

    //Separa dia, mes y anio y las pone en vectores
    for(int i = 0; i < primeraFechaSize; i++){

        //cout << charPrimeraFecha[i]; //Debug

        //Checa en que guion de la fecha va en el array
        if(charPrimeraFecha[i] == '-'){
            contadorGuion++;
        }

        //Agrega la parte del dia a un vector
        if(charPrimeraFecha[i] != '-' && contadorGuion == 0){
            diaTemp.push_back(charPrimeraFecha[i]);
        }

        //Agrega la parte del mes a un vector
        if(charPrimeraFecha[i] != '-' && contadorGuion == 1){
            mesTemp.push_back(charPrimeraFecha[i]);
        }

        //Agrega la parte del anio a un vector
        if(charPrimeraFecha[i] != '-' && contadorGuion == 2){
            anioTemp.push_back(charPrimeraFecha[i]);
        }
    }

    string tempString; //Para almacenar los strings que se van a convertir a ints

    //Vector a integer
    tempString = vectorToString(diaTemp);
    diaPrimero = stoi(tempString);
    tempString = vectorToString(mesTemp);
    mesPrimero = stoi(vectorToString(mesTemp));
    tempString = vectorToString(anioTemp);
    anioPrimero = stoi(vectorToString(anioTemp));

    diaTemp.clear();
    mesTemp.clear();
    anioTemp.clear();

    //Separacion segunda fecha
    contadorGuion = 0; //Reinicia el contador de guiones

    //Separa dia, mes y anio y las pone en vectores
    for(int i = 0; i < segundaFechaSize; i++){

        //Checa en que guion de la fecha va en el array
        if(charSegundaFecha[i] == '-'){
            contadorGuion++;
        }

        //Agrega la parte del dia a un vector
        if(charSegundaFecha[i] != '-' && contadorGuion == 0){
            diaTemp.push_back(charSegundaFecha[i]);
        }

        //Agrega la parte del mes a un vector
        if(charSegundaFecha[i] != '-' && contadorGuion == 1){
            mesTemp.push_back(charSegundaFecha[i]);
        }

        //Agrega la parte del anio a un vector
        if(charSegundaFecha[i] != '-' && contadorGuion == 2){
            anioTemp.push_back(charSegundaFecha[i]);
        }
    }

    //Vector a integer
    tempString = vectorToString(diaTemp);
    diaSegundo = stoi(tempString);
    tempString = vectorToString(mesTemp);
    mesSegundo = stoi(vectorToString(mesTemp));
    tempString = vectorToString(anioTemp);
    anioSegundo = stoi(vectorToString(anioTemp));


    //Debug para checar que se esten convirtiendo correctamente y compararlo
//    cout << "\nDia 1: " << diaPrimero << endl;
//    cout << "Mes 1: " << mesPrimero << endl;
//    cout << "Anio 1: " << anioPrimero << endl;
//
//    cout << "\nDia 2: " << diaSegundo << endl;
//    cout << "Mes 2: " << mesSegundo << endl;
//    cout << "Anio 2: " << anioSegundo << endl;


    //Comparacion de fechas
    if(anioPrimero > anioSegundo){ //Anio A mayor B
        return 1;
    }
    else if(anioPrimero < anioSegundo){ //Anio B mayor A
        return 2;
    }
    else{ //Anio A igual a B
        if(mesPrimero > mesSegundo){ //Mes A mayor B
            return 1;
        }
        else if(mesPrimero < mesSegundo){ //Mes A menor B
            return 2;
        }
        else{
            if(diaPrimero > diaSegundo){ //Dia A mayor B
                return 1;
            }
            else if(diaPrimero < diaSegundo){ //Dia A menor B
                return 2;
            }
            else{ //Fecha A y B son igual
                return 3;
            }
        }
    }
}

int main()
{
    string fechaA = "10-8-2020"; //Control
    string fechaB = "11-8-2020"; //Dia despues del control
    string fechaC = "12-8-2020"; //Dos dias despues del control
    string fechaD = "10-9-2020"; //Un mes despues del control
    string fechaE = "10-8-2019"; //Un anio antes del control

    cout << "Dia despues " << compararFechas(fechaA, fechaB) << endl;
    cout << "\nDos dias despues " << compararFechas(fechaA, fechaC) << endl;
    cout << "\nMes despues " << compararFechas(fechaA, fechaD) << endl;
    cout << "\nAnio antes " << compararFechas(fechaA, fechaE) << endl;
    cout << "\nMes luego dia " << compararFechas(fechaD, fechaA) << endl;
    cout << "\nAnio luego dia " << compararFechas(fechaE, fechaA) << endl;
    cout << "\nIguales " << compararFechas(fechaA, fechaA) << endl;

    return 0;
}
