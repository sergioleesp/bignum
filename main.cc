#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>

#include "bignum.h"
#include "cmdline.h"

using namespace std;

// Variables globales
multiplication_algorithm_t selected_algorithm;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

// Funciones para procesar argumentos en linea de comando
static void opt_help(string const &);
static void opt_input(string const &);
static void opt_output(string const &);
static void opt_multiplication(string const &);

// Descripcion de argumentos en linea de comando
static option_t options[] = {
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "multiplication", "karatsuba", opt_multiplication, OPT_DEFAULT},
	{0, },
};

// Indica informacion acerca de como ejecutar el programa
static void opt_help(string const &arg)
{
	cout << "cmdline [-m karatsuba/standard] " << endl;
	cout << "cmdline [-i file] [-o file]" << endl;
	cout << "cmdline [-h]" << endl;
	exit(0);
}

// Asigna el stream de entrada correspondiente
static void opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	if (arg == "-") 
		iss = &cin;
	else 
	{
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	if (!iss->good())
	{
		cerr << "[Error]: Cannot open " << arg << endl;
		exit(1);
	}
}

// Asigna el stream de salida correspondiente
static void opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	if (arg == "-")
		oss = &cout;
		
	else 
	{
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}
	// Verificamos que el stream este OK.
	if (!oss->good())
	{
		cerr << "[Error]: Cannot open " << arg << endl;
		exit(1);
	}
}

// Asigna el algoritmo de multiplicacion correspondiente
static void opt_multiplication(string const &arg)
{
	if(arg == "standard")
		selected_algorithm = STANDARD;
	else if (arg == "karatsuba")
		selected_algorithm = KARATSUBA;
	else
	{
		cerr << "[Error]: Invalid multiplication algorithm, try 'standard' or 'karatsuba'" << endl;
		exit(1);
	}
}

int main(int argc, char * const argv[])
{
	// Instanciamos la linea de comando
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	// Instanciamos el bignum resultado con el algoritmo de multiplicacion correspondiente
	bignum result;
	result.set_algorithm(selected_algorithm);

	while(*iss >> result) 
	{	
		*oss << result << endl;

		if (oss->bad())
		{
			cerr << "[Error]: Cannot write to output stream" << endl;
			return (1);
		}
	}
	return 0;
}