/* DEFINICIONES DE CODIGO + LIBRERIAS */
#include "code.hpp"
#include <iostream>
#include <conio.h>

void menu() {
	system("cls");
	std::cout << "========== MENU ==========\n";
	std::cout << "[1] Presionar techa \n";
	std::cout << "[2] Salir\n";

}
void mun1() {
	char secondchar;
	system("cls");
	std::cout << "========== Presionar techa ==========\n\n";
	char mychar = _getch();
	long intchar = static_cast<int>(mychar);
	if (mychar == -32) {
		secondchar = _getch();
		intchar = intchar << 8 | secondchar;
	} 
	std::cout << "El caracter obtenido fue: \"" << mychar << "\" con el codigo: " << intchar << "\n\n";
	
	
	system("pause");
}
