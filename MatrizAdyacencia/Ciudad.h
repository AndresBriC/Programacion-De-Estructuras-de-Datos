#ifndef CIUDAD_H_INCLUDED
#define CIUDAD_H_INCLUDED

#include <string>

class Ciudad{
    std::string nombre;
    int numHabitantes;

public:
    Ciudad();
    Ciudad(std::string _nombre, int numHabitantes);
    ~Ciudad();

    std::string getNombre();
    int getNumHabitantes();

    friend std::ostream &operator <<(std::ostream &, const Ciudad &);

private:


};

#endif // CIUDAD_H_INCLUDED
