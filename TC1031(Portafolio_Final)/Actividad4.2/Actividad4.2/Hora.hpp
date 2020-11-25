//
//  Hora.hpp
//  Act_4.2
//
//  Created by inigo guerra on 20/11/20.
//

#ifndef Hora_hpp
#define Hora_hpp

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

#endif /* Hora_hpp */
