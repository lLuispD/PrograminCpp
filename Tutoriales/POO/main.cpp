
//*************************************
//Pila C++

#include <iostream>
#include <string>

using namespace std;
//Nodo:
class nodo
{
public:
	int dato;
	nodo* siguiente;
	nodo() {
		this->dato = 0;
		this->siguiente = NULL;
	}
};
//pila
class pila {
public:
	//pila tamaño

	nodo* tope;
	int tamanio;
	pila() {
		this->tamanio = 0;
		this->tope = NULL;
	}
	//insertar nodo:
	void insertar(int n) {
		nodo* nuevo = new nodo();
		nuevo->dato = n;
		nuevo->siguiente = this->tope;
		this->tope = nuevo;
		cout << "nodo " << n << " insertado correctamente" << endl;
		this->tamanio++;
	}
	//imprimir pila
	void imprimir() {
		nodo* aux = this->tope;
		while (aux != NULL) {
			cout << "Dato: " << aux->dato << endl;
			aux = aux->siguiente;
		}
	}
};

int main() {
	system("title PILARES");
	int opcion;
	int n;
	pila a = pila();
	do {
		system("cls");
		cout << "[1] insertar \n";
		cout << "[2] Imprimir \n";
		cout << "[3] salir \n";
		cout << "ingrese una opcion \n";
		cin >> opcion;
		if (opcion == 1) {
			system("cls");
			cout << "ingrese un numero" << endl;
			cin >> n;
			a.insertar(n);
			system("pause");
		}
		else if (opcion == 2) {
			system("cls");
			cout << "pila: " << endl;
			a.imprimir();
			system("pause");
		}

	} while (opcion != 3);
	return 0;
}