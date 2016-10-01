#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>

using namespace std;

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
     * Engancha al padre con alguno de los hijos de nodo en lugar de el.
     * Requiere padre != NULL
     * Requiere 'nodo' es hijo directo de padre
     */
    void saltearNodo(Nodo *padre, Nodo *nodo);

    /*
     * Imprime en pantalla recursivamente a partir de un nodo.
     */
    void inOrder(std::ostream &os, Nodo *nodo) const;

};

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v)
        : valor(v), izq(NULL), der(NULL) {}

template<class T>
Conjunto<T>::Nodo::~Nodo(){
    delete der;
    delete izq;
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
    Nodo *padre = raiz_;
    if (padre == NULL) {
        raiz_ = new Nodo(clave);
        cardinal_++;
    }
    while (padre != NULL) {
        if (clave == padre->valor) return;
        if (clave > padre->valor) {
            if (padre->der == NULL) {
                padre->der = new Nodo(clave);
                cardinal_++;
                break;
            } else {
                padre = padre->der;
            }
        } else {
            if (padre->izq == NULL) {
                padre->izq = new Nodo(clave);
                cardinal_++;
                break;
            } else {
                padre = padre->izq;
            }
        }
    }
}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinal_;
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    // Busco el nodo a eliminar y su padre. Si el nodo a buscar es NULL no hago nada.
    Nodo *padre = raiz_;
    Nodo *actual = NULL;
    if (padre == NULL) return;
    while (padre != NULL) {
        if (clave > padre->valor) {
            if (padre->der == NULL) return;
            if (clave == padre->der->valor) {
                actual = padre->der;
                break;
            }
            padre = padre->der;
        } else if (clave < padre->valor) {
            if (padre->izq == NULL) return;
            if (clave == padre->izq->valor) {
                actual = padre->izq;
                break;
            }
            padre = padre->izq;
        } else if (clave == padre->valor) {
            actual = padre->der;
        }
    }

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
const int Conjunto<T>::cantHijos(const Nodo *nodo) const {
    int cont = 0;
    if (nodo->izq != NULL) cont++;
    if (nodo->der != NULL) cont++;
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
    // Eliminar hoja
    if ((padre->der != NULL) && (padre->der->valor == hoja->valor)) {
        // actual esta a la derecha de su padre
        padre->der = NULL;
    } else {
        // actual esta a la derecha de su padre
        padre->izq = NULL;
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

#endif // CONJUNTO_HPP_
