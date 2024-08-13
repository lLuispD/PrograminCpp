// Este es un archivo de libreria .hpp para tener menus por consola

#pragma once

#ifdef MENU_EXPORTS
#define MENU_API __declspec(dllexport)
#else
#define MENU_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <iostream>  


// Clase menu. para poder crear varios menus por consola. 
namespace menus { 

	// Clase menu para menus por consola
	class menu {
	public:

		// Constructor(N° Opciones , Titulo del menu)
		menu(int optionCount  , const std::string& title );		
		// Obtener el titulo del menu <string>
		std::string getName();
		// Mostrar menu
		void show() const;
		// Mostrar y esperar opcion del menu <int> // Retorna Opcion - 1
		int Show_getOption();
		// Nombrar opcion(indice , nombre)
		void setOption(int index, const std::string& option);	
		// Retorna el nombre de la opcion <string>(indice)
		std::string getOption(int index) const;
		// Retorna el indice por el nombre de la opcion <int>(Nombre)
		int getIndex(std::string mOption) const;

		

	private:

		int m_optionCount;
		std::string m_title;
		std::vector<std::string> m_options;						// Array dinámico para las opciones
		
	};
	
	
};
