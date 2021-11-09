#include "bignum.h"

// Parte privada

// Funcion valor absoluto
bignum abs(const bignum &n)
{
	bignum c = n;
	c.sign = 0;

	return c;
}

// Funcion quitar 0
void remove_zeros(bignum &n)
{	
	// En caso de que le pase un arreglo lleno de 0
	if(n == 0)
		n = 0;

	// Mientras que la primera posicion del arreglo sea 0
	else if(n.digits[0] == 0 && n.size > 1)
	{	
		// Si entro al if es porque hay por lo menos un cero
		size_t zeros = 1;

		while(n.digits[zeros] == 0)
			zeros++;

		n.size -= zeros;

		short_t *aux = new short_t[n.size];

		for(size_t i = 0; i < n.size; i++)
			aux[i] = n.digits[i + zeros];

		delete[] n.digits;

		n.digits = new short_t[n.size];

		for(size_t i = 0; i < n.size; i++)
			n.digits[i] = aux[i];

		delete[] aux;
	}
}

bool size_even(const bignum &n)
{
    if(n.size % 2 || n.size == 1)
        return false;

    return true;
}

// Funcion suma
bignum sum(const bignum &a, const bignum &b, const bool &s)
{	
	size_t size = 0;
	size_t aux_a = 0;
	size_t aux_b = 0;

	// Por propiedad de la suma el tamaño del resultado no puede ser mayor que 
	// el numero mas grande + 1
	if(a.size >= b.size)
	{
		size = a.size + 1;
		aux_a = a.size - b.size;
	}
	else
	{
		size = b.size + 1;
		aux_b = b.size - a.size;
	}
	bignum c(size);
	c.sign = s;

	for(size_t i = c.size - 1; i < c.size; i--)
	{	
		if(i - aux_b - 1 < a.size)
			c.digits[i] += a.digits[i - aux_b - 1];

		if(i - aux_a - 1 < b.size)
			c.digits[i] += b.digits[i - aux_a - 1];

		if(c.digits[i] > 9)
		{
			c.digits[i] -= 10;
			c.digits[i - 1]++;
		}	
	}
	remove_zeros(c);
	return c;
}

// Funcion resta
bignum subtraction(const bignum &a, const bignum &b)
{	
	short_t bigger = 0;
	short_t count = 0;
	size_t size = 0;
	size_t diff = 0;
	short aux = 0;

	// Guardo el mayor tamaño y la diferencia entre los tamaños
	size = max(a.size, b.size);
	diff = size - min(a.size, b.size);

	bignum c(size);

	// Verifico que numero es mayor en modulo
	if(abs(a) == abs(b))
		return c = 0;

	else if(abs(b) > abs(a))
		bigger++;

	// Consideraciones de signo
	//
	// Si B es mayor y negativo, A positivo
	if(bigger && b.sign && !a.sign)
		c.sign = 1;
	// Si A es mayor y negativo, B positivo
	else if(!bigger && a.sign && !b.sign)	
		c.sign = 1;
	// Si B es mayor y ambos numeros son positivos
	else if(bigger && !b.sign && !a.sign)
		c.sign = 1;
	// Si A es mayor y ambos numeros son negativos
	else if(!bigger && a.sign && b.sign)
		c.sign = 1;

	// Ejecuto la resta dependiendo que numero tiene mayor modulo, restando 
	// del mas chico al mas grande
	for(size_t i = size - 1; i < size; i--)
	{	
		if(bigger)
		{
			// Ejecuto la resta en un short para representar los negativos
			if(i - diff < a.size)
				aux = b.digits[i] - a.digits[i - diff];
			// Para los digitos que no tegan coincidente
			else
				aux = b.digits[i];
		}
		else
		{
			// Ejecuto la resta en un short para representar los negativos
			if(i - diff < b.size)
				aux = a.digits[i] - b.digits[i - diff];
			// Para los digitos que no tegan coincidente
			else
				aux = a.digits[i];
		}
		if(count)
		{
			aux--;
			count--;
		}
		if(aux < 0)
		{
			aux += 10;
			count++;
		}
		c.digits[i] = aux;
	}
	remove_zeros(c);

	//Si el resultado es 0, saco el signo
	if(c == 0)
		c.sign = 0;

	return c; 
}

// Funcionar achicar
bignum reduce(const bignum &n, const size_t &from, const size_t &to)
{	
	if(to <= from)
	{
		bignum c = 0;
		return c; 
	}
	else
	{
		bignum c(to - from);
	
		for(size_t i = 0; i < c.size; i++)
		{		
			if(from + i < to)
				c.digits[i] = n.digits[from + i];
		}

		// En caso de que haya agarrado solo ceros
		if(c.digits[0] == 0 && c.size != 1)
		{
			for(size_t i = 0; i < c.size; i++)
				if(c.digits[i] != 0)
					return c;

			return c = 0;
		}
		return c;
	}
}

// Funcion enlarge
bignum enlarge(const bignum &n, const size_t &zeros)
{	
	bignum c(n.size + zeros);

	if(!zeros)
		c = n;
	else
	{
		for(size_t i = 0; i < n.size; i++)
			c.digits[i] = n.digits[i];
	}
	return c;
}

// Funcion para agregar ceros
void add_zeros(bignum &n, const ssize_t &zeros)
{
	if(zeros > 0)
	{
		short_t *aux = new short_t[n.size];

		for(size_t i = 0; i < n.size; i++)
			aux[i] = n.digits[i];

		delete[] n.digits;
		n.digits = new short_t[n.size += zeros];

		for(size_t i = 0; i < n.size; i++)
		{
			if(i < n.size - zeros)
				n.digits[i] = aux[i];
			else
				n.digits[i] = 0;
		}

		delete[] aux;
	}
	else if(zeros < 0)
	{
		short_t *aux = new short_t[n.size + zeros];

		for(size_t i = 0; i < n.size + zeros; i++)
			aux[i] = n.digits[i];

		delete[] n.digits;
		n.digits = new short_t[n.size += zeros];

		for(size_t i = 0; i < n.size; i++)
				n.digits[i] = aux[i];
		
		delete[] aux;	
	}
}

// Multiplicacion estandar
bignum standard(const bignum &a, const bignum &b)
{	
	// Por propiedad de la multiplicacion, el resultado de la misma no puede
	// ser mas grande que la 
	size_t size = a.size + b.size;
	short_t aux = 0;

	bignum c(size);

	// En caso de que alguno de los numeros sea 0
	if(a == 0 || b == 0)
		return c = 0;

	// Considero los casos en los que el resultado podria ser negativo
	c.sign = a.sign ^ b.sign;

	// Ejecuto la multiplicacion
	for (long i = a.size - 1; i >= 0; i--)
	{
   		for (long j = b.size - 1; j >= 0; j--)
   		{
            aux = c.digits[i + j + 1] + a.digits[i] * b.digits[j];
            c.digits[i + j + 1] = aux % 10;
            c.digits[i + j] += aux / 10;
            aux = 0;
        }
    }
    remove_zeros(c);
	return c;
}

// Multiplicacion Karatsuba con bignums
bignum karatsuba(const bignum &a, const bignum &b)
{	
	bignum a_ = abs(a);
	bignum b_ = abs(b);
	bignum c;

	// Casos base
	if(a_ == 0 || b_ == 0)
		return c = 0;

	if(a_.size < 2 || b_.size < 2)
		return standard(a, b);

	size_t diff = max(a_.size, b_.size) - min(a_.size, b_.size);

	// Si la diferencia es 0 y ambos numeros son de tamaño impar
	if(!diff)
	{	
		// Fuerzo la paridad de ambos numeros
		if(!size_even(a_.size) && !size_even(b_.size))
		{
			add_zeros(a_, 1);
			add_zeros(b_, 1);
			diff += 2;
		}
	}
	// En caso de que A sea de mayor tamaño que B
	else if(a_.size > b_.size)
	{	
		// Fuerzo la paridad de ambos numeros
		if(!size_even(a_.size))
		{	
			add_zeros(a_, 1);
			add_zeros(b_, diff + 1);
			diff += 2;
		}
		else
			add_zeros(b_, diff);
	}
	// En caso de que B sea de mayor tamaño que A
	else if(b_.size > a_.size)
	{	
		// Fuerzo la paridad de ambos numeros
		if(!size_even(b_.size))
		{	
			add_zeros(b_, 1);
			add_zeros(a_, diff + 1);
			diff += 2;
		}
		else
			add_zeros(a_, diff);
	}
	// Obtengo la base
	size_t n = a_.size; 
	size_t m = n / 2;

	// Obtengo recursivamente las 3 multiplicaciones
	bignum x = karatsuba(reduce(a_, 0, m), reduce(b_, 0, m));
	bignum y = karatsuba(reduce(a_, m, a_.size), reduce(b_, m, b_.size));
	bignum z = karatsuba(reduce(a_, 0, m) + reduce(a_, m, a_.size), 
		       reduce(b_, 0, m) + reduce(b_, m, b_.size)) - x - y;

	if(x == 0 && y == 0 && z == 0)
		return c = 0;

	// Ejecuto la multiplicacion de Karatsuba
	add_zeros(x, n);
	add_zeros(z, m);
	c = x + y + z;
	c.sign = a.sign ^ b.sign;

	if(diff)
		add_zeros(c, -diff);

	return c;
}

// Funcion de division
// Funciona de manera practicamente instantanea cuando la diferencia
// entre los tamaños de A y B no es mayor a 3
bignum division(const bignum &a, const bignum &b, bignum &remainder)
{	
	bignum c;

	// Verfico que el dividendo no sea 0 ni menor al divisor
	// No uso la funcion abs porque se que division es llamada con abs
	if(a == 0 || b > a)
		return c = 0;

	// Incializo C en 1 ya que por lo anterior B debe caber por lo menos una
	// vez en A
	bignum aux = a - b;
	c = 1;

	// Voy restando B en A hasta que el resultado sea negativo. Voy contando
	// la cantidad de veces que se ejecute la resta
	while(1)
	{
		aux = aux - b;
		
		if(aux.sign)
		{	
			remainder = aux + b;
			break;
		}
		c = c + 1;
	}
	remove_zeros(c);
	return c;
}

// Funcion de division recursiva
bignum division_rec(const bignum &a, const bignum &b)
{	
	bignum remainder = 0;

	// Caso base
	if(a.size < (b.size + 2))
		return division(a, b, remainder);

	// Divido los b.size + 3 digitos de A por B teniendo en cuenta 
	// multiplicar al resultado por la base 10 elevada a a.size - b.size -3
	// Y vuelvo a llamar a la funcion de manera recursiva para que se
	// ejecute con el remanente del numero A sacandole los b.size + 3 digitos
	// primeros
	return division_rec(reduce(a, b.size + 1, a.size) + (enlarge(remainder, a.size - b.size - 1)), b)
		   + enlarge(division(reduce(a, 0, b.size + 1), b,remainder), a.size - b.size - 1);
}

// Parte publica

// Constructor sin Argumentos
bignum::bignum()
{	
	type = KARATSUBA;
	digits = NULL;
	size = 0;
	sign = 0;
}

// Constructor por tamaño
bignum::bignum(const size_t &s)
{	
	// Por las dudas, agrego la condicion de tamaños nulos o negativos
	if(s <= 0)
	{	
		type = KARATSUBA;
		digits = NULL;
		size = 0;
		sign = 0;
	}

	type = KARATSUBA;
	digits = new short_t[s];
	size = s;
	sign = 0;

	// Me aseguro que C este lleno de 0
	for (size_t i = 0; i < size; i++)
		digits[i] = 0;
}

// Constructor con argumento
bignum::bignum(const string &str, bool s = 0)
{	
	type = KARATSUBA;
	string aux;
	// Guardo el tamaño del string
	size = str.size();
	// Creo un arreglo del tamaño del string
	digits = new short_t[size];

	// Guardo los numeros del string en mi bignum
	for(size_t i = 0; i < size; i++)
	{
		aux = str[i]; 
		digits[i] = (short_t)stoi(aux);
	}
	sign = s;
}

// Constructor por bignum
bignum::bignum(const bignum &n)
{	
    // En caso de que right este apuntando a NULL
    if(!n.digits)
    {	
    	type = KARATSUBA;
        digits = NULL;
        size = 0;
        sign = 0;
    }
    else
    {	
    	type = n.type;
        digits = new short_t[n.size];
        size = n.size;
        sign = n.sign;

        // Copio los valores del arreglo right en this
        for(size_t i = 0; i < size; i++)
             digits[i] = n.digits[i];
    }
}

// Constructor por entero
bignum::bignum(const int &n)
{	
	type = KARATSUBA;

	// Chequeo el signo del entero
    if(n < 0)
        sign = 1;
    else
        sign = 0;

	// Convierto el entero a string
    string str = to_string(n);
    // Guardo el tamaño del string
    size = str.size() - sign;
    // Creo un arreglo del tamaño del string
    digits = new short_t[size];

    string aux;
    // Guardo los numeros del string en mi bignum
    for(size_t i = 0; i < size; i++)
    {
        aux = str[i + sign];
        digits[i] = (short_t)stoi(aux);
    }
}

// Constructor por copia
bignum& bignum::operator = (const bignum &right)
{	
	// Verifico si los bignum a igualar son distintos
	if(&right != this)
	{	
		// Borro el puntero de this
		delete[] digits;

		// En caso de que right este apuntando a NULL
		if(!right.digits)
		{	
			type = KARATSUBA;
			digits = NULL;
			size = 0;
			sign = 0;
		}
		else
		{	
			type = right.type;
			digits = new short_t[right.size];
			size = right.size;
			sign = right.sign;

			// Copio los valores del arreglo right en this
			for(size_t i = 0; i < size; i++)
				digits[i] = right.digits[i];
		}
	}
	// Devuelvo un puntero a mi bignum this
	return *this;
}

// Constructor por copia con entero
bignum& bignum::operator = (const int &right)
{	
	// Creo un bignum pasando el entero a un string
	bignum aux(to_string(right));

	return *this = aux;
}

// Destructor
bignum::~bignum() {delete[] digits;}

// Funcion seteo de algoritmo de multiplicacion
void bignum::set_algorithm(const multiplication_algorithm_t &algorithm)
{
	if(algorithm == STANDARD)
		type = STANDARD;
	else
		type = KARATSUBA;	
}

// Operador de suma
bignum operator + (const bignum &a, const bignum &b)
{	
	// Ambos numeros son positivos
	if(!a.sign && !b.sign)
		return sum(a, b, 0);

	// A positivo y B negativo
	if(!a.sign && b.sign)
		return subtraction(a, b);

	// A negativo y B positivo
	if(a.sign && !b.sign)
		return subtraction(a, b);

	// Ambos numeros son negativos
	return sum(a, b, 1);
}

// Operador de suma entre bignum y entero
bignum operator + (const bignum &a, const int &n)
{	
	// Creo un bignum C usando el constructor por string
	return a + bignum(to_string(n));
}

// Operador de resta
bignum operator - (const bignum &a, const bignum &b)
{	
	// Ambos numeros son positivos
	if(!a.sign && !b.sign)
		return subtraction(a, b);

	// A positivo y B negativo
	if(!a.sign && b.sign)
		return sum(a, b, 0);

	// A negativo y B positivo
	if(a.sign && !b.sign)
		return sum(a, b, 1);

	// Ambos numeros son negativos
	return subtraction(a, b);
}

// Operador de resta entre bignum y entero
bignum operator - (const bignum &a, const int &n)
{	
	// Creo un bignum C usando el constructor por string
	return a - bignum(to_string(n));
}

// Operador de multiplicacion
bignum operator * (const bignum &a, const bignum &b)
{	
	bignum c;

	if(a.type == STANDARD)
		c = standard(a, b);
	else
		c = karatsuba(a, b);

	return c;
}

// Operador de division
bignum operator / (const bignum &a, const bignum &b) 
{	
	// Creo el bignum resultado con el que operar
	bignum c;

	// Si el divisor es 0 devuelvo el bignum NULL
	if(b == 0)
		return c;

	// Si el dividendo es 0 o el divisor es mayor al dividendo
	if(a == 0 || abs(b) > abs(a))
		return c = 0;

	// Si A y B son iguales en modulo
	if(abs(a) == abs(b))
	{
		c = 1;
		c.sign = a.sign ^ b.sign;
		return c;
	}				
	// Si divido por 1
	if(abs(b) == 1)
	{
		c = abs(a);
		c.sign = a.sign ^ b.sign;
		return c;
	} 
	c = division_rec(abs(a), abs(b));
	c.sign = a.sign ^ b.sign;
	return c;
} 

// Operador de salida
ostream& operator << (ostream &os, bignum &n)
{	
	if(n.digits == NULL)
		return os;

	if(n.sign && n != 0)
		os << "-";

	for (size_t i = 0; i < n.size; i++)
		os << n.digits[i];

	delete[] n.digits;
	n.digits = NULL;
    return os;
}

// Operador de entrada
istream& operator >> (istream &is, bignum &result)
{
	// Utilizamos el codigo de Shunting Yard
	stack<char> operations;
	queue<string> output;
	string input;

	// Obtengo la cadena de entrada
	getline(is, input);

	// Entrada vacia
	if(input.empty())
		return is;

	// Parseo la entrada
	for(size_t i = 0; i < input.size(); i++)
	{	
		if(isblank(input[i])){}

		// Si identifico un numero
		else if(isdigit(input[i]))
		{	
			size_t pos = i++;
			size_t len = 1;
			while(isdigit(input[i]))
			{
				len++;
				i++;
			}
			i--;
			output.push(input.substr(pos, len));
		}

		// Si identifico un negativo
		else if(input[i] == '-')
		{
			size_t j = i;
			while(j != 0 && isblank(input[--j])){}

			// Tengo una resta
			if(isdigit(input[j]) || input[j] == ')')
			{
				if(!operations.empty())
				{
					while(operations.top() == '-' || operations.top() == '+' || operations.top() == '*' || operations.top() == '/')
						output.push(string{operations.pull()});
				}	
				operations.push(input[i]);
			}
			// Tengo un negativo
			else
				output.push(string{"s"});
		}

		else if(input[i] == '+')
		{
			size_t j = i;
			while(j != 0 && isblank(input[--j])){}

			// Tengo una suma
			if(isdigit(input[j]) || input[j] == ')')
			{
				if(!operations.empty())
				{
					while(operations.top() == '-' || operations.top() == '+' || operations.top() == '*' || operations.top() == '/')
						output.push(string{operations.pull()});
				}
				operations.push(input[i]);
			}
			// Si tengo un positivo no hago nada
		}

		else if(input[i] == '*' || input[i] == '/')
		{	
			if(!operations.empty())
			{
				while(operations.top() == '*' || operations.top() == '/')
					output.push(string{operations.pull()});
			}
			operations.push(input[i]);
		}
		// Si identifico un parentesis de apertura
		else if(input[i] == '(')
			operations.push(input[i]);

		// Si identifico un parentesis de cerrado
		else if(input[i] == ')')
		{
			if(operations.empty())
			{	
				cout << "Syntax Error" << endl;
				return is;
			}
			while(!operations.empty() && operations.top() != '(')
				output.push(string{operations.pull()});

			if(!operations.empty())
				operations.pull();
			else
			{	
				cout << "Syntax Error" << endl;
				return is;
			}
		}
	}

	if(!operations.empty())
	{
		if(operations.top() == '(' && output.empty())
		{
			cout << "Syntax Error" << endl;
			return is;
		}
		else
		{	
			if(output.empty())
			{
				cout << "Syntax Error" << endl;
				return is;
			}
			else
			{	
				while(!operations.empty())
					output.push(string{operations.pull()});
			}
		}
	}

	// Resuelvo la entrada
	string aux;
	short_t sign = 0;
	stack<bignum> numbers;

	while(!output.empty())
	{
		aux = output.pull();

		if(isdigit(aux[0]))
		{
			numbers.push(bignum(aux, sign));
			if(sign)
				sign--;
		}
		else if(aux[0] == 's')
			sign++;
		else if(numbers.length() < 2)
		{
			cout << "Syntax Error" << endl;
			return is;
		}
		else if(aux[0] == '+')
		{	
			result = numbers.pull();
			result = numbers.pull() + result;
			numbers.push(result);
		}
		else if(aux[0] == '-')
		{	
			result = numbers.pull();
			result = numbers.pull() - result;
			numbers.push(result);
		}
		else if(aux[0] == '*')
		{	
			result = numbers.pull();
			result = numbers.pull() * result;
			numbers.push(result);
		}
		else if(aux[0] == '/')
		{	
			result = numbers.pull();
			result = numbers.pull() / result;
			numbers.push(result);
		}
	}
	if(!numbers.empty())
		result = numbers.pull();
	else
	{
		cout << "Syntax Error" << endl;
		return is;
	}
	return is;
}

// Operador de comparacion
bool operator == (const bignum &a, const bignum &b)
{	
	// En caso de que los numeros sean de distinto tamaño y llenos de ceros
	if(a.size != b.size)
	{	
		for(size_t i = 0; i < a.size; i++)
		{
			if(a.digits[i] != 0)
				return false;
		}
		for(size_t i = 0; i < b.size; i++)
		{
			if(b.digits[i] != 0)
				return false;
		}
		return true;
	}

	if(a.sign != b.sign)
		return false;
	
	for (size_t i = 0; i < a.size; i++)
	{
		if (a.digits[i] != b.digits[i])
		 	return false;
	}	 	
	return true;	 	
}

// Operador de comparacion bignum y entero
bool operator == (const bignum &a, const int &b)
{
	bignum c(to_string(b));
	
	if(a == c)
		return true;

	return false;
}

// Operador distinto
bool operator != (const bignum &a, const bignum &b)
{
	if(a == b)
		return false;

	return true;	 	
}

// Operador distinto bignum y entero
bool operator != (const bignum &a, const int &n)
{
    bignum c(to_string(n));

    if(a != c)
        return true;

    return false;
}

// Operador mayor
bool operator > (const bignum &a, const bignum &b)
{
	if(a.size < b.size)
		return false;

	if(a.size > b.size)
		return true;

	if(!a.sign && b.sign)
		return true;

	if(a.sign && !b.sign)
		return false;	
	
	if(a == b)
		return false;

	for (size_t i = 0; i < a.size; i++)
	{
		if (a.digits[i] > b.digits[i])
			return true;

		else if(a.digits[i] < b.digits[i])
			return false;
	}	 	
	return false;	 	
}

// Operador menor
bool operator < (const bignum &a, const bignum &b)
{
	if(a > b)
		return false;

	if(a == b)
		return false;	 	

	return true;	 	
}