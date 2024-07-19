#include <iostream>
#include "menu.hpp"
#include <conio.h>

int main() {
	char userChar;
	menus::menu metodos(5, "Metodos numericos");
	metodos.setOption(0, "Ecuaciones no lineales");
	menus::menu ec_nolineal(5, metodos.getOption(0));
	ec_nolineal.setOption(0, "Punto fijo");
	
	metodos.show();
	
	userChar = _getch();
	metodos.getOption(userChar);


	




	return 0;
}
