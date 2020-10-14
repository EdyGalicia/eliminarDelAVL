#pragma once

#include<iostream>
#include"NodoAVL.h"
#include<stdbool.h>
#include<string>
#include <ostream>
#include <sstream>
#include <fstream>
using namespace std;

class Arbol
{
public:
	Arbol();
	~Arbol();
	NodoAVL* getRaiz();
	void setRaiz(NodoAVL* n);
	void insertar(int valor);
	void eliminar(int dato);
private:
	NodoAVL* raiz;
	NodoAVL* insertar(NodoAVL* raiz, int dato, bool& hc);

	//ROTACIONES
	NodoAVL* rotacionII(NodoAVL* n, NodoAVL* n1);
	NodoAVL* rotacionDD(NodoAVL* n, NodoAVL* n1);
	NodoAVL* rotacionID(NodoAVL* n, NodoAVL* n1);
	NodoAVL* rotacionDI(NodoAVL* n, NodoAVL* n1);

	//ELIMINAR
	NodoAVL* borrarAVL(NodoAVL* raiz, int dato, bool& hc);
	NodoAVL* reemplazar(NodoAVL* n, NodoAVL* act, bool& hc);
	NodoAVL* equilibrar1(NodoAVL* n, bool& hc);
	NodoAVL* equilibrar2(NodoAVL* n, bool& hc);


	//DELETE
	void Delete(NodoAVL* raiz);
};

