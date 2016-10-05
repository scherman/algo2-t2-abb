#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>

using namespace std;

//  g++ Conjunto.hpp tests.cpp && valgrind --leak-check=yes --show-leak-kinds=all ./a.out

template<class T>
class Conjunto {
public:

    // Constructor. Genera un conjunto vacío.
    Conjunto();

    // Destructor. Debe dejar limpia la memoria.
    ~Conjunto();

    // Inserta un elemento en el conjunto. Si éste ya existe,
    // el conjunto no se modifica.
    void insertar(const T &);

    // Decide si un elemento pertenece al conjunto o no.
    bool pertenece(const T &) const;

    // borra un elemento del conjunto. Si éste no existe,
    // el conjunto no se modifica.
    void remover(const T &);

    // devuelve el mínimo elemento del conjunto según <.
    const T &minimo() const;

    // devuelve el máximo elemento del conjunto según <.
    const T &maximo() const;

    // devuelve la cantidad de elementos que tiene el conjunto.
    unsigned int cardinal() const;

    // muestra el conjunto.
    void mostrar(std::ostream &) const;

    friend ostream &operator<<(ostream &os, const Conjunto<T> &c) {
        c.mostrar(os);
        return os;
    }

private:

    // la representación de un nodo interno.
    struct Nodo {
        // el constructor, toma el elemento al que representa el nodo.
        Nodo(const T &v);

        ~Nodo();

        // el elemento al que representa el nodo.
        T valor;
        // puntero a la raíz del subárbol izq.
        Nodo *izq;
        // puntero a la raíz del subárbol der.
        Nodo *der;
    };

    // puntero a la raíz de nuestro árbol.
    Nodo *raiz_;
    int cardinal_;

    // funciones auxiliares


    /*
     * Ubica al nodo cuyo valor es 'clave' y devuelve a su padre
     * Si la clave no existe y 'enganchar' es true, devuelve al padre al cual se engancharía.
     * Si la clave no existe y 'enganchar' es false, devuelve NULL.
     * Si el arbol es nil, devuelve NULL.
     */
    Nodo* nodoPadre(const T& clave, const bool enganchar) const;

    /*
     * Dado un nodo, devuelve un 0 <= m <= 2 que representa la cantidad de hijos.
     */
    const int cantHijos(const Nodo *nodo) const;

    /*
     * Desengancha 'hoja' de su padre
     * Requiere padre != NULL
     * Requiere 'hoja' es hijo directo de padre
     */
    void desengancharHoja(Nodo *padre, Nodo *hoja);

    /*
     * Engancha 'hoja' con su padre
     * Requiere padre, hoja != NULL
     * Requiere padre->valor != hoja->valor
     */
    void engancharHoja(Nodo *padre, Nodo *hoja);

    /*
     * Engancha al padre con alguno de los hijos de nodo en lugar de el.
     * Requiere padre != NULL
     * Requiere 'nodo' es hijo directo de padre
     */
    void saltearNodo(Nodo *padre, Nodo *nodo);

    /*
     * Imprime en pantalla recursivamente a partir de un nodo.
     */
    void inOrder(std::ostream &os, Nodo *nodo) const;

    /*
     * Devuelve true si nodo es hijo de padre.
     * Requiere que nodo != NULL
     * Si padre es null, devuelve false
     */
    bool esHijo(const Nodo* padre, const T& clave) const;


};

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v)
        : valor(v), izq(NULL), der(NULL) {}

template<class T>
Conjunto<T>::Nodo::~Nodo(){
    delete der; // No hace falta preguntar si es null
    delete izq; // No hace falta preguntar si es null
}


template<class T>
Conjunto<T>::Conjunto() : raiz_(NULL), cardinal_(0) {}

template<class T>
Conjunto<T>::~Conjunto() {
    delete raiz_;
}

template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    Nodo *actual = raiz_;
    while (actual != NULL) {
        if (clave == actual->valor) return true;
        if (clave > actual->valor) {
            actual = actual->der;
        } else {
            actual = actual->izq;
        }
    }
    return false;
}

template<class T>
void Conjunto<T>::insertar(const T &clave) {
    Nodo *padre = nodoPadre(clave, true);
    if (padre == NULL) {
        // El arbol es nil
        raiz_ = new Nodo(clave);
    } else {
        if (esHijo(padre, clave)) return;
        Nodo* nuevo = new Nodo(clave);
        engancharHoja(padre, nuevo);
    }
    cardinal_++;
}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinal_;
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    // Busco el nodo a eliminar y su padre.
    if (raiz_ == NULL) return;
    if (raiz_->valor == clave) {
        delete raiz_;
        raiz_ = NULL;
        cardinal_--;
        return;
    }
    Nodo *padre = nodoPadre(clave, false);
    if (padre == NULL) return; // La clave no existe
    Nodo *actual = clave > padre->valor ? padre->der : padre->izq;

    // Borro el nodo mediante el algoritmo correspondiente.
    switch (cantHijos(actual)) {
        case 0:
            desengancharHoja(padre, actual);
            delete actual;
            break;
        case 1:
            saltearNodo(padre, actual);
            delete actual;
            break;
        case 2:
            // Busco min en el subarbol derecho y lo pongo en actual
            Nodo *minPadre = actual;
            Nodo *min = minPadre->der;
            while (min != NULL) {
                if (min->izq == NULL) break;
                minPadre = min;
                min = min->izq;
            }
            if (min == NULL) min = minPadre;
            actual->valor = min->valor;

            // Eliminar el nodo min original (sabemos que tiene 0 ó 1 hijos)
            if (cantHijos(min) == 1) saltearNodo(minPadre, min);
            if (cantHijos(min) == 0) desengancharHoja(minPadre, min);
            delete min;
            break;
    }
    cardinal_--;
}

template<class T>
const T &Conjunto<T>::minimo() const {
    Nodo* min = raiz_;
    while(min != NULL) {
        if (min->izq == NULL) return min->valor;
        min = min->izq;
    }
}

template<class T>
const T &Conjunto<T>::maximo() const {
    Nodo *max = raiz_;
    while (max != NULL) {
        if (max->der == NULL) return max->valor;
        max = max->der;
    }
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &os) const {
    os << "{";
    inOrder(os, raiz_);
    os << "}";
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::nodoPadre(const T& clave, const bool enganchar) const {
    Nodo* padre = raiz_;
    while (padre != NULL) {
        if (clave > padre->valor) {
            if (padre->der == NULL) {
                // La clave no existe
                if (enganchar) return padre;
                return NULL;
            }
            if (clave == padre->der->valor) return padre; // Encontre el nodo
            padre = padre->der;
        } else if (clave < padre->valor) {
            if (padre->izq == NULL) {
                // La clave no existe
                if (enganchar) return padre;
                return NULL;
            }
            if (clave == padre->izq->valor) return padre; // Encontre el nodo
            padre = padre->izq;
        }
    }
    return NULL;
}


template<class T>
const int Conjunto<T>::cantHijos(const Nodo *nodo) const {
    int cont = 0;
    if ( (nodo->izq != NULL) || (nodo->der != NULL) ) cont++;
    return cont;
}


template<class T>
void Conjunto<T>::saltearNodo(typename Conjunto<T>::Nodo *padre, typename Conjunto<T>::Nodo *nodo) {
    if ((padre->der != NULL) && (padre->der->valor == nodo->valor)) {
        // nodo esta a la derecha de su padre
        if (nodo->der != NULL) {
            // el hijo de nodo esta del lado derecho
            padre->der = nodo->der;
            nodo->der = NULL;
        } else {
            // el hijo de nodo esta del lado izquierdo
            padre->der = nodo->izq;
            nodo->izq = NULL;
        }
    } else {
        // nodo esta a la izquierda de su padre
        if (nodo->der != NULL) {
            // el hijo de nodo esta del lado derecho
            padre->izq = nodo->der;
            nodo->der = NULL;
        } else {
            // el hijo de nodo esta del lado izquierdo
            padre->izq = nodo->izq;
            nodo->izq = NULL;
        }
    }
}


template<class T>
void Conjunto<T>::desengancharHoja(typename Conjunto<T>::Nodo *padre, typename Conjunto<T>::Nodo *hoja) {
    if ((padre->der != NULL) && (padre->der->valor == hoja->valor)) {
        // actual esta a la derecha de su padre
        padre->der = NULL;
    } else {
        // actual esta a la derecha de su padre
        padre->izq = NULL;
    }
}

template<class T>
void Conjunto<T>::engancharHoja(typename Conjunto<T>::Nodo *padre, typename Conjunto<T>::Nodo *hoja) {
    if (hoja->valor > padre->valor) {
        // Hoja debe ubicarse del lado derecho de su padre
        padre->der = hoja;
    } else {
        // Hoja debe ubicarse del lado izquierdo de su padre
        padre->izq = hoja;
    }
}



template<class T>
void Conjunto<T>::inOrder(std::ostream &os, typename Conjunto<T>::Nodo *nodo) const{
    if (nodo == NULL) return;
    if (nodo->izq != NULL) {
        inOrder(os, nodo->izq);
        os << ", ";
    }
    os << nodo->valor;
    if (nodo->der != NULL) {
        os << ", ";
        inOrder(os, nodo->der);
    }
}

template<class T>
bool Conjunto<T>::esHijo(const typename Conjunto<T>::Nodo *padre, const T &clave) const{
    if (padre == NULL) return false;
    if ( (padre->der != NULL) && (padre->der->valor == clave) ) return true;
    if ( (padre->izq != NULL) && (padre->izq->valor == clave) ) return true;
    return false;
}

#endif // CONJUNTO_HPP_
