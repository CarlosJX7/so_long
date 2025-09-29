
#include <stdio.h>                      // incluir printf para imprimir por pantalla

typedef int (*op_alias)(int, int);      // alias de tipo: puntero a función int(int,int)

int suma(int a, int b)                  // función normal que suma dos enteros
{
	return a + b;                       // devolver la suma
}

int resta(int a, int b)                 // función normal que resta dos enteros
{
	return a - b;                       // devolver la resta
}

int producto(int m, int n)              // función normal que multiplica dos enteros
{
	return m * n;                       // devolver el producto
}

int cociente(int r, int s)              // función normal que divide dos enteros (división entera)
{
	return r / s;                       // devolver el cociente (ojo: s no debe ser 0)
}

int operacion(int (*f)(int,int), int x, int y) // recibe un puntero a función y dos enteros
{
	return f(x, y);                     // invocar el callback con x e y
}

int operacion_alias(op_alias funcion, int i, int j) // versión usando el alias de puntero a función
{
	return funcion(i, j);               // invocar el callback-alias con i y j
}

int main(int argc, char const *argv[])  // programa principal
{
	(void)argc;                         // evitar warning por parámetro no usado
	(void)argv;                         // evitar warning por parámetro no usado
	int a;                              // operando 1
	int b;                              // operando 2
	
	a = 40;                             // asignar valor a
	b = 2;                              // asignar valor b

	int sum;                            // resultado de la suma
	sum = operacion(suma, a, b);        // pasar suma como callback sin typedef
	printf("Resultado de la operacion: %d\n", sum); // imprimir resultado suma
	
	int res;                            // resultado de la resta
	res = operacion_alias(resta, a, b); // pasar resta como callback con typedef
	printf("Resultado de la operacion: %d\n", res); // imprimir resultado resta
	
	int (*p_funcion)(int, int);         // puntero a función sin typedef
	p_funcion = producto;               // asignar dirección de producto al puntero sin typedef
	int prod;                           // resultado del producto
	prod = p_funcion(a, b);             // invocar a través del puntero
	printf("Resultado de la operacion: %d\n", prod); // imprimir resultado producto
	
	op_alias division = cociente;       // puntero a función con typedef, apunta a cociente
	int coc;                            // resultado de la división
	coc = division(a, b);               // invocar a través del alias (apunta a cociente)
	printf("Resultado de la operacion: %d\n", coc);  // imprimir resultado cociente
	
	return 0;                           // terminar programa correctamente
}


/*#include <stdio.h>

typedef int (*op_alias)(int, int);

int suma(int a, int b)
{
	return a + b;
}

int resta(int a, int b)
{
	return a - b;
}

int operacion(int (*f)(int,int), int x, int y)
{
	return f(x, y);
}

int producto(int m, int n)
{
	return  m * n;
}

int cociente(int r, int s)
{
	return r / s;
}

int operacion_alias(op_alias funcion, int i, int j)
{
	return funcion(i, j);
}
int main(int argc, char const *argv[])
{
	int a;
	int b;
	int sum;
	int res;
	int (*p_funcion)(int, int);
	int prod;
	op_alias division = cociente;
	int coc;

	a = 40;
	b = 2;
	sum = operacion(suma, a, b);
	printf("Resultado de la operacion: %d\n", sum);
	res = operacion_alias(resta, a, b);
	printf("Resultado de la operacion: %d\n", res);
	p_funcion = producto;
	prod = p_funcion(a, b);
	printf("Resultado de la operacion: %d\n", prod);
	coc = division(a, b);
	printf("Resultado de la operacion: %d\n", coc);
	return 0;
}
*/
