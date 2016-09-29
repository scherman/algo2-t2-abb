#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
using namespace std;

template <class T>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);

		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;

		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);

		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;

		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;

		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// muestra el conjunto.
		void mostrar(std::ostream&) const;

		friend ostream& operator<<(ostream& os, const Conjunto<T> &c) {
			c.mostrar(os);
			return os;
		}

	private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der; 
		};

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz_;
        int cardinal_;

	// funciones auxiliares

    /*
     * Dado un nodo, devuelve un 0 <= m <= 2 que representa la cantidad de hijos.
     */
    const int cantHijos(const Nodo & nodo) const;

    /*
     * Dado un T cualquiera, devuelve:
     * - Si pertenece al arbol, el nodo padre al nodo cuyo elemento es T
     * - Si no pertenece al arbol, el nodo padre al tendria que engancharse si se agregara
     * Si el arbol es nil, su padre es NULL.
     */
    const Nodo & nodoPadre(const T & clave) const;
//    const std::vector inOrder(const T&) const;

};

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL)
{}

template <class T>
Conjunto<T>::Conjunto() : raiz_(NULL), cardinal_(0)
{}

template <class T>
Conjunto<T>::~Conjunto()
{ 
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = raiz_;
    while (actual != NULL){
        if (clave == actual->valor) return true;
        if (clave > actual->valor) {
            actual = actual->der;
        } else {
            actual = actual->izq;
        }
    }
	return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave)
{
    Nodo* nuevoElemento = new Nodo(clave);
    Nodo* padre = raiz_;
    if (padre == NULL) {
        raiz_ = nuevoElemento;
        cardinal_++;
    }
    while(padre != NULL){
        if (clave == padre->valor) return;
        if (clave > padre->valor){
            if (padre->der == NULL){
                padre->der = nuevoElemento;
                cardinal_++;
                break;
            } else {
                padre = padre->der;
            }
        } else {
            if (padre->izq == NULL){
                padre->izq = nuevoElemento;
                cardinal_++;
                break;
            } else {
                padre = padre->izq;
            }
        }
    }
}

template <class T>
unsigned int Conjunto<T>::cardinal() const
{
	return cardinal_;
}

template <class T>
void Conjunto<T>::remover(const T& clave)
{
    Nodo* actual = raiz_;
    while(actual != NULL) {
        if (clave == actual->valor) {
            switch(cantHijos(*actual)) {
                case 0:

                case 1:

                case 2:
                    ;
            }
        }
        if (clave > actual->valor) {
            actual = actual->der;
        } else {
            actual = actual->izq;
        }
    }
}

template <class T>
const T&  Conjunto<T>::minimo() const
{
	T t;
	return t;
}

template <class T>
const T&  Conjunto<T>::maximo() const
{
	T t;
	return t;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
    std::cout << "";
}

template <class T>
const int Conjunto<T>::cantHijos(const Nodo & nodo) const {
    return (nodo.izq == NULL) + (nodo.der == NULL);
}

template <class T>
const Nodo & Conjunto<T>::nodoPadre(const T & clave) const {
    Nodo* actual = raiz_;
    if (cardinal() <= 1) return NULL
    while(actual != NULL) {
        if (clave > actual->valor) {
            // O lo encontre/ubique, o sigo recorriendo
            if ((actual->der == NULL) || (clave == actual->der->valor)) return actual;
            actual = actual->der;
        } else {
            // O lo encontre/ubique, o sigo recorriendo
            if ((actual->izq == NULL) || (clave == actual->izq->valor)) return actual;
            actual = actual->izq;
        }
    }
}
//const std::vector inOrder(const T&) const; {
////    std::vector<T> v;
////    return array;
//}


#endif // CONJUNTO_HPP_
