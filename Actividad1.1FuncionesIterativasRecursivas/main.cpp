#include <iostream>

using namespace std;


/*
Explicaci�n de complejidad Iterativa

Es de tipo lineal
*/
int sumaIterativa(int n){

    int sumaActual = 0;

    for(int i = 1; i <= n; i++){
        sumaActual += i;
    }

    return sumaActual;
}

/*
Explicaci�n de complejidad Recursiva

Es de tipo lineal
*/
int sumaRecursiva(int n){

    if(n != 0){
        return n + sumaRecursiva(n-1);
    }
    else{ //Al llegar n a 0 regresa la constante 0
        return 0;
    }
}

/*
Explicaci�n de complejidad Directa

Es de tipo constante
*/
int sumaDirecta(int n){

    return (n*(n+1))/2;
}

int main()
{
    int sumTarget;

    do{
        cout << "Escriba un valor positivo sin decimales de n para hacer la sumatoria de 1 a n: ";
        cin >> sumTarget;
    }
    while(sumTarget <= 2);

    cout << "Resultados:\nIterativa: " << sumaIterativa(sumTarget) << "\nRecursiva: " << sumaRecursiva(sumTarget)<< "\nDirecta:   " << sumaDirecta(sumTarget) << endl;

    cout << "Para 15\nIterativa: " << sumaIterativa(15) << "\nRecursiva: " << sumaRecursiva(15)<< "\nDirecta:   " << sumaDirecta(15) << endl;

    cout << "Para 50\nIterativa: " << sumaIterativa(50) << "\nRecursiva: " << sumaRecursiva(50)<< "\nDirecta:   " << sumaDirecta(50) << endl;

    cout << "Para 321:\nIterativa: " << sumaIterativa(321) << "\nRecursiva: " << sumaRecursiva(321)<< "\nDirecta:   " << sumaDirecta(321) << endl;

    return 0;
}
