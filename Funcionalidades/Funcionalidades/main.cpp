#include "code.hpp"
#include <conio.h>
#include <iostream>

char option;

int main() {
	//system("tittle: ver ascii");
inicio:
	menu();
	option = _getch();

	if (option == '1') {
		mun1();
		goto inicio;
	} else if (option == '2') {
		return 0;
	} else goto inicio;

	return 0;
}



