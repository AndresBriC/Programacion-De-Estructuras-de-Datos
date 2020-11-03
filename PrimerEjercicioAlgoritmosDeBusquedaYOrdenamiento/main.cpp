#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std;

template <typename T>
int busqueda(vector<T> numeros, T valor){

    int i = 0;
    int encontrado = -1;

    int vectorSize = numeros.size();

    while (encontrado == -1 && i < vectorSize){
        if(numeros[i] ==  valor){
            encontrado = i;
        }
        ++i;
    }

    return encontrado;
}

int generaInt(){
    return rand()%100;
}

float generaFloat(){
    return rand()%100 * 0.5;
}


int main(){

    vector<int> numeros;

    //Tamaño del vector
    const int N = 10;

    //Definir la seed
    srand (time(0));

    //Generar numeros aleatorios
    for(int i=0; i<N; ++i){
        numeros.push_back(generaInt());
        cout << numeros.back() << ", ";
    }
    cout << endl;

    int valor;
    cout << "Que numero quieres buscar? ";
    cin >> valor;

    int result = busqueda(numeros, valor);

    //Validacion de busqueda
    if (result == -1){
        cout << "El valor solicitado no fue encontrado" << endl;
    }
    else{
        cout << "El valor solicitado se encuentra en el indice " << result << endl;
    }

    return 0;
}
