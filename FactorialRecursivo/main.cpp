#include <iostream>

using namespace std;

long long int factorial(int n){

    //Condicion de parada
    if (n == 0){
        return 1;
    }
    //Paso Recursivo
    else{
        return n * factorial(n-1);
    }
}

int main(int argc, const char * argv[]){ //Argumentos para usasr en la terminal

    int n = -1;

    //Entrar el numero a calcular el factorial
    do{
    cout << "Entre el numero: ";
    cin >> n;
    }
    while(n < 0); //Validacion para evitar potencias negativas

    //Calcular el factorial de n
    long long int resultado = factorial(n);

    //Mostrar el resultado
    cout << "El factorial de " << n << " es = " << resultado << endl;

    return 0;
}
