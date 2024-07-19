// Este es un archivo de libreria .hpp para tener menus por consola

#pragma once

#include <string>
#include <vector>
#include <iostream>  



// Clase menu. para poder crear varios menus.
namespace menus { 
	
	class menu {
	public:

		menu(int optionCount, const std::string& title);		// Metodo constructor (numero de opciones , titulo del menu)
		void show() const;										// Mostrar menu en consola
		void setOption(int index, const std::string& option);	// Nombrar opcion(indice , nombre)
		std::string getOption(int index) const;					// Retorna el nombre de la opcion

	private:
		int m_optionCount;
		std::string m_title;
		std::vector<std::string> m_options; // Array dinámico para las opciones
		

	};
};


