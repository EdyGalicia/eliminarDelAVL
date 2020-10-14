#pragma once

#include<iostream>
using namespace std;

class NodoAVL
{
public:
	NodoAVL(int dato);
	void setDato(int dato);
	void setFactor(int factor);
	void setIzquierda(NodoAVL* izq);
	void setDerecha(NodoAVL* der);
	NodoAVL* getIzquierda();
	NodoAVL* getDerecha();
	int getDato();
	int getFactor();
private:
	int dato;
	int factorE;
	NodoAVL* izquierda;
	NodoAVL* derecha;
};

