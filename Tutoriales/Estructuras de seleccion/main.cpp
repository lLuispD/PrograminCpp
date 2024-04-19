//---------------------------|
// Estructuras de seleccion  |
//---------------------------|

#include <iostream>
using namespace std;
int edad;
int numero;
int main() {
	for (int i = 1; i < 5; i = i + 1) {
		cout << "Ingrese su edad: ";
		cin >> edad;
		if (edad >= 18 && edad < 50) {					// && significa and, || significa and
			cout << "usted es mayor de edad, pero joven " << endl;
		}
		else {
			if (edad < 18) {
				cout << "usted es menor de edad" << endl;
			}
			else {
				cout << "usted es muy mayor de edad" << endl;
			}
		}
	}
	cout << endl;
	cout << "------------------------- " << endl;
	cout << endl;
	cout << "Ingrese un valor: ";
	cin >> numero;
	switch (numero) {
	case 1:
		cout << "el valor es uno" << endl;
		break;
	case 2:
		cout << "el valor es dos" << endl;
		break;
	case 3:
		cout << "el valor es tres" << endl;
		break;
	default:
		cout << "el valor es diferente de 1, 2, 3. " << endl;
		break;
	}
	return 0;
}
