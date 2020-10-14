#include "Arbol.h"


using namespace std;

Arbol::Arbol() {
	this->raiz = NULL;
}

Arbol::~Arbol() {
	Delete(this->raiz);
}

void Arbol::Delete(NodoAVL* raiz) {
	if (raiz == NULL)
	{
		return;
	}
	else
	{
		Delete(raiz->getIzquierda());
		Delete(raiz->getDerecha());
		delete raiz;
	}
}


//ROTACIONES
NodoAVL* Arbol::rotacionII(NodoAVL* n, NodoAVL* n1) {
	n->setIzquierda(n1->getDerecha());
	n1->setDerecha(n);
	if (n1->getFactor() == -1) // va a ser -1 cuando n1 no tenga hijo derecho
	{
		n->setFactor(0);
		n1->setFactor(0);
	}
	else
	{
		n->setFactor(-1);
		n1->setFactor(1);
	}
	return n1;
}

NodoAVL* Arbol::rotacionDD(NodoAVL* n, NodoAVL* n1) {
	n->setDerecha(n1->getIzquierda());
	n1->setIzquierda(n);
	if (n1->getFactor() == 1)//n1 va a tener factor 1 cuando no tenga hijo izquierdo
	{
		n->setFactor(0);
		n1->setFactor(0);
	}
	else
	{
		n->setFactor(1);
		n1->setFactor(-1);
	}
	return n1;
}

NodoAVL* Arbol::rotacionID(NodoAVL* n, NodoAVL* n1) {
	NodoAVL* n2 = n1->getDerecha();
	n->setIzquierda(n2->getDerecha());
	n2->setDerecha(n);
	n1->setDerecha(n2->getIzquierda());
	n2->setIzquierda(n1);

	//corregir factores de equilibrio
	if (n2->getFactor() == 1)//si n2 solo trae un hijo derecho
	{
		n1->setFactor(-1);
	}
	else//si trae dos o ningun hijo
	{
		n1->setFactor(0);
	}

	//si n2 solo trae un hijo izquierdo
	if (n2->getFactor() == -1)
	{
		n->setFactor(1);
	}
	else
	{
		n->setFactor(0);
	}
	n2->setFactor(0);
	return n2;
}

NodoAVL* Arbol::rotacionDI(NodoAVL* n, NodoAVL* n1) {
	NodoAVL* n2 = n1->getIzquierda();
	n->setDerecha(n2->getIzquierda());
	n2->setIzquierda(n);
	n1->setIzquierda(n2->getDerecha());
	n2->setDerecha(n1);

	//corregir factores de equilibrio
	if (n2->getFactor() == 1)//si solo trae un hijo derecho
	{
		n->setFactor(-1);
	}
	else//si trae dos o ningun hijo
	{
		n->setFactor(0);
	}

	//si n2 solo trae un hijo izquierdo
	if (n2->getFactor() == -1)
	{
		n1->setFactor(1);
	}
	else
	{
		n1->setFactor(0);
	}
	n2->setFactor(0);
	return n2;
}


//eliminar
NodoAVL* Arbol::borrarAVL(NodoAVL* raiz, int dato, bool& hc)
{
	if (raiz == NULL)
	{
		cout << "Nodo no encontrado" << endl;
	}
	else if (dato < raiz->getDato())
	{
		NodoAVL* izq = borrarAVL((NodoAVL*)raiz->getIzquierda(), dato, hc);
		raiz->setIzquierda(izq);
		if (hc)
		{
			raiz = equilibrar1(raiz, hc);
		}
	}
	else if (dato > raiz->getDato())
	{
		NodoAVL* der = borrarAVL((NodoAVL*)raiz->getDerecha(), dato, hc);
		raiz->setDerecha(der);
		if (hc)
		{
			raiz = equilibrar2(raiz, hc);
		}
	}
	else // si es igual
	{
		NodoAVL* q;
		q = raiz; // nodo que se va a eliminar
		if (q->getIzquierda() == NULL)
		{
			raiz = q->getDerecha();
			hc = true;
		}
		else if (q->getDerecha() == NULL)
		{
			raiz = q->getIzquierda();
			hc = true;
		}
		else // si tiene hijo izquierdo y derecho
		{
			NodoAVL* izq = reemplazar(raiz, raiz->getIzquierda(), hc);
			raiz->setIzquierda(izq);
			if (hc)
			{
				raiz = equilibrar1(raiz, hc);
			}
		}
		q = NULL;
	}
	return raiz;
}

NodoAVL* Arbol::reemplazar(NodoAVL* n, NodoAVL* act, bool& hc) // se utiliza el mayor de los menores
{
	if (act->getDerecha() != NULL)
	{
		NodoAVL* d = reemplazar(n, act->getDerecha(), hc);
		act->setDerecha(d);
		if (hc)
		{
			act = equilibrar2(act, hc);
		}
	}
	else
	{
		n->setDato(act->getDato());
		n = act;
		act = act->getIzquierda();
		n = NULL;
		hc = true;
	}
	return act;
}

NodoAVL* Arbol::equilibrar1(NodoAVL* n, bool& hc)
{
	NodoAVL* n1;
	switch (n->getFactor())
	{
	case -1:
		n->setFactor(0);
		break;
	case 0:
		n->setFactor(1);
		hc = false;
		break;
	case 1: //se aplica un tipo de rotacion derecha
		n1 = n->getDerecha();
		if (n1->getFactor() >= 0)
		{
			if (n1->getFactor() == 0) // la altura no vuenve a disminuir
			{
				hc = false;
			}
			n = rotacionDD(n, n1);
		}
		else
		{
			n = rotacionDI(n, n1);
		}
		break;
	default:
		break;
	}
	return n;
}

NodoAVL* Arbol::equilibrar2(NodoAVL* n, bool& hc)
{
	NodoAVL* n1;
	switch (n->getFactor())
	{
	case -1: // se aplica un tipo de rotacion izquierda
		n1 = n->getIzquierda();
		if (n1->getFactor() <= 0)
		{
			if (n1->getFactor() == 0)
			{
				hc = false;
			}
			n = rotacionII(n, n1);
		}
		else
		{
			n = rotacionID(n, n1);
		}
		break;
	case 0:
		n->setFactor(-1);
		hc = false;
		break;
	case 1:
		n->setFactor(0);
		break;
	default:
		break;
	}
	return n;
}



//INSERTAR
NodoAVL* Arbol::insertar(NodoAVL* raiz, int dato, bool& hc) {
	NodoAVL* n1;
	if (raiz == NULL)
	{
		raiz = new NodoAVL(dato);
		hc = true;
	}
	else if (dato < raiz->getDato())
	{
		NodoAVL* izq = insertar(raiz->getIzquierda(), dato, hc);
		raiz->setIzquierda(izq);
		if (hc)
		{
			switch (raiz->getFactor())
			{
			case 1:
				raiz->setFactor(0);
				hc = false;
				break;
			case 0://si no llevaba ningun hijo
				raiz->setFactor(-1);
				break;
			case -1:
				n1 = raiz->getIzquierda();
				if (n1->getFactor() == -1)
				{
					raiz = rotacionII(raiz, n1);
				}
				else
				{
					raiz = rotacionID(raiz, n1);
				}
				hc = false;
				break;
			default:
				break;
			}
		}
	}
	else if (dato > raiz->getDato())
	{
		NodoAVL* der = insertar(raiz->getDerecha(), dato, hc);
		raiz->setDerecha(der);//raiz va a ser el nodo que mandamos a insertar
		if (hc)//si estamos creciendo
		{
			switch (raiz->getFactor())
			{
			case 1://si es uno, crecio hacia la derecha
				n1 = raiz->getDerecha();
				if (n1->getFactor() == 1)//si crecio dos veces a la derecha
				{
					raiz = rotacionDD(raiz, n1);
				}
				else
				{
					raiz = rotacionDI(raiz, n1);
				}
				hc = false;
				break;
			case 0://si no llevaba ningun hijo
				raiz->setFactor(1);
				break;
			case -1:
				raiz->setFactor(0);
				hc = false;
				break;
			default:
				break;
			}
		}
	}
	return raiz;
}

void Arbol::insertar(int valor) {
	bool b = false;
	bool* a = &b;
	this->raiz = insertar(this->raiz, valor, *a);
}

void Arbol::eliminar(int dato)
{
	bool b = false;
	bool* a = &b;
	this->raiz = borrarAVL(this->raiz, dato, *a);
}


//RAIZ
NodoAVL* Arbol::getRaiz() { return this->raiz; }
void Arbol::setRaiz(NodoAVL* n) { this->raiz = n; }