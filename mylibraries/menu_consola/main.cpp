
/*	
	CODIGO DE EJEMPLO:

	NOTAS DE LA ULTIMA VISITA:

	*	Se agrego el obtener la opcion <int> menus::Show_getOption()
	* 
*/
 

#include <iostream>
#include "menu.hpp"
#include <conio.h>


int main() {
	system("title Ejemplo menus");
	menus::menu main(3,"Este es el menu");
	menus::menu submenu1(3, "Submenu 1");
	menus::menu submenu2(3, "Submenu 2");
	menus::menu submenu3(3, "Submenu 3");
	
	main.setOption(0, submenu1.getName()); 
	main.setOption(1, submenu2.getName()); 
	main.setOption(2, submenu3.getName()); 

	submenu1.setOption(0, "opcion 1");
	submenu1.setOption(1, "opcion 2");
	submenu1.setOption(2, "opcion 3");

	submenu2.setOption(0, "opcion1"); 


	switch (main.Show_getOption()) {
	case 1 -1: submenu1.Show_getOption(); break;
	case 2 - 1: submenu2.show(); break;
	case 3 - 1: submenu3.show(); break;
	default:	break;
	}

	_getch();
    return 0;
}
