#ifndef HORA_H_INCLUDED
#define HORA_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

class Hora{
private:
    int hora, minuto, segundo;

public:
    //Constructores
    Hora();
    Hora(int cHora, int cMinuto, int cSegundo);

    //Accessors
    int getHora();
    int getMinuto();
    int getSegundo();

    //Mutators
    void setHora(int mHora);
    void setMinuto(int mMinuto);
    void setSegundo(int mSegundo);

    //Sobrecarga de operadores
    friend ostream & operator<<(ostream & os, const Hora & hora);
    friend bool operator!= (const Hora &h1, const Hora &h2);
    friend bool operator== (const Hora &h1, const Hora &h2);
    friend bool operator> (const Hora &h1, const Hora &h2);
    friend bool operator< (const Hora &h1, const Hora &h2);

    //Metodos complementarios
    Hora stringToHora(string horaATransformar);
    string vectorToString(vector<char> vectToConv);

};

#endif // HORA_H_INCLUDED
