#include "NodoAVL.h"

NodoAVL::NodoAVL(int dato) {
	this->dato = dato;
	this->izquierda = NULL;
	this->derecha = NULL;
}

void NodoAVL::setDato(int dato) { this->dato = dato; }
void NodoAVL::setFactor(int factor) { this->factorE = factor; }
void NodoAVL::setIzquierda(NodoAVL* izq) { this->izquierda = izq; }
void NodoAVL::setDerecha(NodoAVL* der) { this->derecha = der; }

int NodoAVL::getDato() { return this->dato; }
int NodoAVL::getFactor() { return this->factorE; }
NodoAVL* NodoAVL::getIzquierda() { return this->izquierda; }
NodoAVL* NodoAVL::getDerecha() { return this->derecha; }