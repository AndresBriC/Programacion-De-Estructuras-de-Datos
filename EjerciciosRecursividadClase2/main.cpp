#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

int euclides(int m, int n) //Ejercicio 1
{
    if((m%n) == 0){ //Si el residuo llega a cero, se cumple la condicion de parada
        return n;
    }
    else{
        return euclides(n, m%n); //Si no se cumple la condicion de parada, toma n como el nuevo m y el residuo como el nuevo n
    }

}

int sumaVector(vector<int> vectorASumar, int position , int currentSum){ //Ejercicio 2

    int vectorSize = vectorASumar.size();

    if(position == vectorSize){
        cout << "posicion " << position << endl;
        return currentSum;
    }
    else{
        cout << "posicion " << position << endl;
        return sumaVector(vectorASumar, position+1, vectorASumar[position] + currentSum);
    }

}

void interfaz(int ej){

    switch (ej){

        case 1: //Algoritmo de Euclides
            int a, b;

            do{
                cout << "Recuerda que M debe ser mayor a N" << endl;

                cout << "M = "; //Numero mayor
                cin >> a;
                cout << "N = "; //Numero menor
                cin >> b;
            }
            while(b > a); //Checa que M sea mayor a N

            cout << "El MCD de " << a << " y " << b << " es " << euclides(a,b) << endl;
            break;

        case 2: //Suma de un vector

            vector<int> vectorGenerado;
            srand(time(0));

            cout << "Vector: ";
            for(int i = 0; i < 10; i++){ //Se genera un vector al azar
                vectorGenerado.push_back(rand()%10);
                cout << vectorGenerado[i] << ", ";
            }
            cout << endl;

            cout << "La suma de los elementos del vector es: " << sumaVector(vectorGenerado, 0 , 0) << endl;
    }
}


int main()
{
    int numeroEj;
    int finish = 1;

    do{
        cout << "Que ejercicio quieres hacer? ";
        cin >> numeroEj;

        interfaz(numeroEj);

        cout << "Deseas continuar 1 = Si 2 = No? ";
        cin >> finish;
    }
    while(finish == 1);


    return 0;
}
