/*
	Este programa sirve de ejemplo para hacer un namespace en varios archivos cpp + hpp
*/

#include "nmspc.hpp"
#include <iostream>


int main() {
	funcion::decirhola();
	
	std::cout << funcion::dat("lpd^2") << std::endl;

	system("pause");
	return 0;
}

