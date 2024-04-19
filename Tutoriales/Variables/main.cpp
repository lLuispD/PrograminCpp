//--------------------------------//
//Este es un ejemplo de variables //
//--------------------------------// 

#include <iostream>				//Bibliotecas para utilizar entradas y saldas

using namespace std;			// Evitamos usar std al utilizar la biblioteca
int entero = 10;				// Valor entero
float decimal = 0.24;			// Valor decimal
char texto = 'a';				// Valor caracter
char textos[12] = "Hola mundo";	// Cadena de valores dinamicos
bool booleano = true;			// Valor booleano

int main() {
	cout << entero << endl;		//  Imprime variables y fin de linea
	cout << decimal << endl;
	cout << texto << endl;
	cout << textos << endl;
	cout << booleano << endl;

	cin.get();					// Esperar enter
	return 0;					// Salida del programa con retorno cero
}

