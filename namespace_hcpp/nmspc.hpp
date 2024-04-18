/*
	Esta parte es la declaracion de las funciones que se realicen
	Este archivo (*.hpp) sera el que se incluira en el archivo principal (main.cpp)
*/

#pragma once

namespace funcion {
	void decirhola();
	
	// Los templates se declaran y definen en el *.hpp
	template <typename t>					// template <typename (name var ) >
	t dat(t dato) {							// (name var) func((namevar) par){}
		return dato;
	}

}