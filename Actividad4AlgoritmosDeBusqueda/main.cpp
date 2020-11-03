#include <iostream>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <iterator>
#include <vector>
#include "Ordenamiento.h"

template <typename T>
int busquedaSecuencial(std::vector<T> vect, T N, T valor){
    int i = 0;
    int encontrado = -1;
    while (encontrado == -1 && i < N){
        if ( valor == vect[i] ) {
            encontrado = i;
        }
         i++;
    }
    return encontrado;
}

template <typename T>
int busquedaSecuencialMovFrente(std::vector<T> vect, T N, T valor){
    int i = 0;
    int encontrado = -1;
    while (encontrado == -1 && i < N){
        if ( valor == vect[i] ) {
            encontrado = i;
        }
         i++;
    }
    return encontrado;
}

template <typename T>
int busquedaSecuencialTransp(std::vector<T> vect, T N, T valor){
    int i = 0;
    int encontrado = -1;
    while (encontrado == -1 && i < N){
        if ( valor == vect[i] ) {
            encontrado = i;
        }
         i++;
    }
    return encontrado;
}

template <typename T>
int busquedaBinaria(std::vector<T> vect, T N, T valor){
    if (N == 0){
        return 0;
    }

    int mitad, inf = 0, sup = N - 1;

    do{
        mitad = (inf + sup) / 2;
        if (valor > vect[mitad]){
            inf = mitad + 1;
        }
        else {
            sup = mitad - 1;
        }
    }
    while (vect[mitad] != valor && inf <= sup);

    std::cout << "Valor: " << valor << std::endl;
    std::cout << "Vect en mitad: " << vect[mitad] << std::endl;
    std::cout << "Mitad: " << mitad << std::endl;


    if (vect[mitad] == valor) {
            return mitad; }
    else {
        return -1;
    }
}


int main() {

    //Establecer la semilla
    srand((unsigned int) time(nullptr));

    //Definir cantidad de elementos
    const int n = 100000;

    //Indice del numero buscado
    int foundIndex = 0;

    //Numero a buscar
    int numToFind;

    //Referencia busquedas
    int searchNum;

    //Pedida del numero a buscar
    std::cout << "Escribe el numero a buscar: ";
    std::cin >> numToFind;
    std::cout << std::endl;

    //Pedida del numero a buscar
    std::cout << "Escribe el tipo de busqueda: 1-secuencial, 2-secuencial con mov al frente, 3-secuencial con transposicion, 4-secuencial con ordenamiento, 5-binaria: ";
    std::cin >> searchNum;
    std::cout << std::endl;



    //Busqueda secuencial
    for(int i = 0; i < 15; i++){

        //Iteration number
        std::cout << "Iteration number: " << i+1 << std::endl;

        //Definir un vector de enteros
        std::vector<int> numeros(n);

        //Generar un vector de números enteros utilizando una función Lambda
        std::generate(numeros.begin(), numeros.end(), [](){return rand() % 100;});

        //Busquedas
        switch(searchNum){
            case 1:{//Busqueda secuencial

                std::cout << "Secuencial normal" << std::endl;

                //Referencia de tiempo antes
                auto t1 = std::chrono::high_resolution_clock::now();

                //Realiza la busqueda y asigna el indice encontrado a la variable foundIndex
                foundIndex = busquedaSecuencial(numeros, n, numToFind);

                //Representacion
                std::cout << "Indice encontrado: " << foundIndex << std::endl;
                std::cout << "Comprobacion: " << numeros[foundIndex] << std::endl;

                //Referencia de tiempo despues
                auto t2 = std::chrono::high_resolution_clock::now();

                //Duracion medida
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

                //Imprime duracion
                std::cout << "Duracion: " << duration << " microsegundos" << std::endl << std::endl;
                break;
            }
            case 2:{ //Secuencial con mov al frente

                std::cout << "Secuencial con mov al frente" << std::endl;

                //Referencia de tiempo antes
                auto t1 = std::chrono::high_resolution_clock::now();

                //Realiza la busqueda y asigna el indice encontrado a la variable foundIndex
                foundIndex = busquedaSecuencialMovFrente(numeros, n, numToFind);

                //Representacion
                std::cout << "Indice encontrado: " << foundIndex << std::endl;
                std::cout << "Comprobacion: " << numeros[foundIndex] << std::endl;

                //Referencia de tiempo despues
                auto t2 = std::chrono::high_resolution_clock::now();

                //Duracion medida
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

                //Imprime duracion
                std::cout << "Duracion: " << duration << " microsegundos" << std::endl << std::endl;
                break;
            }
            case 3:{ //Secuencial con transposicion

                std::cout << "Secuencial con transposicion" << std::endl;

                //Referencia de tiempo antes
                auto t1 = std::chrono::high_resolution_clock::now();

                //Realiza la busqueda y asigna el indice encontrado a la variable foundIndex
                foundIndex = busquedaSecuencialTransp(numeros, n, numToFind);

                //Representacion
                std::cout << "Indice encontrado: " << foundIndex << std::endl;
                std::cout << "Comprobacion: " << numeros[foundIndex] << std::endl;

                //Referencia de tiempo despues
                auto t2 = std::chrono::high_resolution_clock::now();

                //Duracion medida
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

                //Imprime duracion
                std::cout << "Duracion: " << duration << " microsegundos" << std::endl << std::endl;

                break;
            }
            case 4:{ //Secuencial con ordenamiento
                //Referencia de tiempo antes

                std::cout << "Secuencial con ordenamiento" << std::endl;

                numeros = Ordenamiento<int>::seleccion(numeros, Ordenamiento<int>::asc);

                auto t1 = std::chrono::high_resolution_clock::now();

                //Realiza la busqueda y asigna el indice encontrado a la variable foundIndex
                foundIndex = busquedaSecuencial(numeros, n, numToFind);

                //Representacion
                std::cout << "Indice encontrado: " << foundIndex << std::endl;
                std::cout << "Comprobacion: " << numeros[foundIndex] << std::endl;

                //Referencia de tiempo despues
                auto t2 = std::chrono::high_resolution_clock::now();

                //Duracion medida
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

                //Imprime duracion
                std::cout << "Duracion: " << duration << " microsegundos" << std::endl << std::endl;

                break;
            }
            case 5:{ //Binaria

                std::cout << "Binaria" << std::endl;

                numeros = Ordenamiento<int>::seleccion(numeros, Ordenamiento<int>::asc);

                //Referencia de tiempo antes
                auto t1 = std::chrono::high_resolution_clock::now();

                //Realiza la busqueda y asigna el indice encontrado a la variable foundIndex
                foundIndex = busquedaBinaria(numeros, n, numToFind);

                //Representacion
                std::cout << "Indice encontrado: " << foundIndex << std::endl;
                std::cout << "Comprobacion: " << numeros[foundIndex] << std::endl;

                //Referencia de tiempo despues
                auto t2 = std::chrono::high_resolution_clock::now();

                //Duracion medida
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

                //Imprime duracion
                std::cout << "Duracion: " << duration << " microsegundos" << std::endl << std::endl;

                break;
            }
        }
    }

    return 0;
}
