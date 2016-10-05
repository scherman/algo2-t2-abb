#include <iostream>
#include "mini_test.h"

#include "Conjunto.hpp"

void test_insertar() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(43);
	c.insertar(2);
	c.insertar(2);
	c.insertar(5);
	ASSERT( c.pertenece(42) );
	ASSERT( c.pertenece(43) );
	ASSERT( c.pertenece(42) );
	ASSERT_EQ( c.pertenece(1),  false);

	// Chequear insertar más elementos
}

void test_cardinal() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(43);
	c.insertar(2);
	c.insertar(2);
	c.insertar(5);
	ASSERT(c.cardinal() == 4 );
}

void test_remover() {
	// Chequear por lo menos los siguientes 3 casos:
	// - Borrar una hoja
	// - Borrar un nodo interno con un hijo
	// - Borrrun nodo interno con dos hijos

    Conjunto<int> b;
    b.remover(44);
    b.remover(42);
    ASSERT(b.cardinal() == 0);
    b.insertar(5);
    b.insertar(7);
    b.insertar(3);
    b.remover(5);
    ASSERT(!(b.pertenece(5)) && (b.cardinal() == 2))

    Conjunto<int> a;
    a.insertar(42);
    a.remover(44);
    a.remover(42);
    ASSERT(!(a.pertenece(42)))

	Conjunto<int> c;
	c.insertar(42);
	c.insertar(44);
	c.insertar(104);
	c.insertar(450);
	c.insertar(-46);
	c.insertar(-460);
	c.insertar(130);
	c.insertar(43);


	bool pertenencia;

	// caso que chequea borrar una hoja
	c.remover(44);
    c.remover(-46);
    c.remover(43);
	pertenencia = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				  && c.pertenece(450) && !c.pertenece(-46) && c.pertenece(-460)
				  && c.pertenece(130) && !c.pertenece(43);
	ASSERT( pertenencia );

}

void test_maximo() {
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(44);
    c.insertar(104);
    c.insertar(450);
    c.insertar(-46);
    c.insertar(-460);
    c.insertar(130);
    c.insertar(43);
    c.mostrar(std::cout);
    int max = c.maximo();
    ASSERT(max == 450) ;
}

void test_minimo() {
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(44);
    c.insertar(104);
    c.insertar(450);
    c.insertar(-46);
    c.insertar(-460);
    c.insertar(130);
    c.insertar(43);
    int min = c.minimo();
    ASSERT(c.minimo() == -460);
}
void test_mleak() {
    // Corriendo valgrind al final de cada instruccion:
    Conjunto<int> c; // total heap usage: 2 allocs, 1 frees, 73,728 bytes allocated
    c.insertar(2); // total heap usage: 3 allocs, 2 frees, 73,752 bytes allocated
    c.insertar(5); // total heap usage: 4 allocs, 3 frees, 73,776 bytes allocated
    c.remover(2); // total heap usage: 4 allocs, 3 frees, 73,776 bytes allocated
    c.remover(5); // total heap usage: 4 allocs, 3 frees, 73,776 bytes allocated
    c.remover(1); // total heap usage: 4 allocs, 3 frees, 73,776 bytes allocated
}


int main() {
//	RUN_TEST(test_insertar);
//	RUN_TEST(test_cardinal)
  RUN_TEST(test_remover);
//	RUN_TEST(test_maximo);
//	RUN_TEST(test_minimo);
//    RUN_TEST(test_mleak);
	return 0;
}

