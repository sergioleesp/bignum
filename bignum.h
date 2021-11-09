#ifndef BIGNUM__H__
#define BIGNUM__H__

#include <iostream>
#include <cstring>
#include <string>

#include "queue.h"
#include "stack.h"

using namespace std;

typedef unsigned short short_t;

// Tipos de algoritmo de multiplicacion
typedef enum
{
    STANDARD,
    KARATSUBA
}
multiplication_algorithm_t;

class bignum
{
private:
	multiplication_algorithm_t type;
	short_t *digits;
	size_t size;
	bool sign;

	friend bignum abs(const bignum &); // Funcion modulo
	friend void remove_zeros(bignum &); // Funcion quitar ceros
	friend bool size_even(const bignum &); // Funcion tamaño par o impar

	friend bignum sum(const bignum &, const bignum &, const bool &); // Funcion suma
	friend bignum subtraction(const bignum &, const bignum &); // Funcion resta

	friend bignum reduce(const bignum &, const size_t &, const size_t &); // Funcion achicar bignums
	friend bignum enlarge(const bignum &, const size_t &); // Funcion agregar ceros
	friend void add_zeros(bignum &, const ssize_t &); // Funcion agregar ceros

	friend bignum standard(const bignum &, const bignum &); // Multiplicacion estandar
	friend bignum karatsuba(const bignum &, const bignum &); // Multiplicacion karatsuba

	friend bignum division(const bignum &, const bignum &, bignum &); // Funcion divison
	friend bignum division_rec(const bignum &, const bignum &); // Funcion division recursiva

public:
	bignum(); // Constructor sin armuentos
	bignum(const size_t &); // Constructor por tamaño
	bignum(const string &, bool); // Constructor con argumento
	bignum(const bignum &); // Constructor por bignum
	bignum(const int &); // Constructor por entero
	bignum& operator = (const bignum &); // Constructor por copia
	bignum& operator = (const int &); // Constructor por copia con entero

	~bignum(); // Destructor

	void set_algorithm(const multiplication_algorithm_t &); // Funcion para elegir la multiplicacion

	friend bignum operator+(const bignum &, const bignum &); // Operador suma
	friend bignum operator+(const bignum &, const int &); // Operador suma bignum y entero

	friend bignum operator-(const bignum &, const bignum &); // Operador resta
	friend bignum operator-(const bignum &, const int &); // Operador resta bignum y entero

	friend bignum operator*(const bignum &, const bignum &); // Operador multiplicacion

	friend bignum operator/(const bignum &, const bignum &); // Operador division

	friend ostream& operator<<(ostream &, bignum &); // Operador de salida
	friend istream& operator>>(istream &, bignum &); // Operador de entrada

	friend bool operator==(const bignum &, const bignum &); // Operador de comparacion
	friend bool operator==(const bignum &, const int &); // Operador de comparacion bignum y entero

	friend bool operator!=(const bignum &, const bignum &); // Operador not	
	friend bool operator!=(const bignum &, const int &); // Operador not bignum y entero

	friend bool operator<(const bignum &, const bignum &); // Operador menor
	friend bool operator>(const bignum &, const bignum &); // Operador mayor
};

#endif



	