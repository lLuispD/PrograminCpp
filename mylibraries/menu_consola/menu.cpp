
#include "menu.hpp"
#include <iostream> 


// Clase menu. para poder crear varios menus.


namespace menus {

	menu::menu(int optionCount, const std::string& title) 
		: m_optionCount(optionCount), m_title(title) {

		m_options.resize(optionCount); // Redimensiona el vector para contener la cantidad de opciones
	}

	void menu::show() const {
		
		system("cls");
		std::cout << "================= " << m_title << " ================= \n\n";
		for (int i = 0; i < m_optionCount; ++i) {
			std::cout << "[" << i + 1 << "] " << m_options[i] << std::endl;
		}  
	}

	void menu::setOption(int index, const std::string& option) {
		if (index < 0 || index >= m_optionCount) {
			throw std::out_of_range("Index out of range");
		}
		m_options[index] = option;
	}

	std::string menu::getOption(int index) const {
		if (index < 0 || index >= m_optionCount) {
			throw std::out_of_range("Index out of range");
		}
		return m_options[index];
	}

} 

