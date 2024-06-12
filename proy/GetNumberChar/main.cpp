#include "main.hpp"
#include <iostream>
#include <conio.h>

char option;

void menu();
void mun1();

int main() {
	//system("tittle: ver ascii");
	inicio:
	menu();
	option = _getch();

	if (option == '1') {
		mun1();
		goto inicio;
	} else if (option == '2') {

	}	else  goto inicio;
	 
	return 0;
}

void menu() {
	system("cls");
	std::cout << "========== MENU ==========\n";
	std::cout << "[1] Presionar techa \n";
	std::cout << "[2] Salir\n";

}
void mun1() {
	system("cls");
	std::cout << "========== Presionar techa ==========\n\n";
	char mychar = _getch();
	int intchar = static_cast<int>(mychar);
	std::cout << "El caracter obtenido fue: \"" << mychar << "\" con el codigo: " << intchar << "\n\n";
	system("pause");
}

