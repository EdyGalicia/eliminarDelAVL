// eliminacionAVL.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include"Arbol.h"

using namespace std;

int main()
{
    Arbol* arbol = new Arbol();
    arbol->insertar(50);
    arbol->insertar(8);
    arbol->insertar(9);
    
    arbol->eliminar(50);
    arbol->eliminar(8);

}

