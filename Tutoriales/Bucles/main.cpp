//---------------------//
// Estos son bucles	   //
//---------------------//

#include <iostream>;			// Biblioteca para utilizar entradas y salidas
using namespace std;			// Evitamos usar std al utilizar la biblioteca

int main() {
	cout << endl;
	// Para bucle While
	int dato = 0;
	while (dato <= 10) {
		cout << "Ingrese un valor mayor a 10 para salir del bucle: ";
		cin >> dato;			// Pedir dato, se almacenará en la variable dato
		cout << "Valor ingresado:" << dato << endl;
	}
	cout << "Fin del loop while" << endl;

	// Para bucle Do While 
	int valor;
	do {
		cout << "Ingrse un valor, cero para salir: ";
		cin >> valor;
		cout << "Valor ingresado: " << valor << endl;
	} while (valor != 0);
	cout << "Fin del loop Do While " << endl;

	// Para loop For
	for (int i = 1; i <= 50; i = i + 1) {
		cout << "El valor de i es: " << i << endl;
	}
	cout << "Fin del loop For ";
	return 0;
}
