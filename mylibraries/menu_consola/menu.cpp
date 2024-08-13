

#include "menu.hpp"
#include <iostream> 


// Clase menu. para poder crear varios menus.


namespace menus {

	menu::menu(int optionCount , const std::string& title)
		: m_optionCount(optionCount), m_title(title) {

		m_options.resize(optionCount);			 // Redimensiona el vector para contener la cantidad de opciones

	}

	std::string menu::getName() {
		return m_title;
	}

	void menu::show() const {

		system("cls");
		std::cout << "================= " << m_title << " ================= \n\n";
		for (int i = 0; i < m_optionCount; ++i) {
			std::cout << "[" << i + 1 << "] " << m_options[i] << std::endl;
		}
	}

	int menu::Show_getOption() {
		std::string str;
		std::string numextract = "";
		int intUser = 0;
		numextract = "";
		intUser = 0;
		do {
			menu::show();
			std::cin >> str;
			numextract = "";

			for (int i = 0; i < str.length(); i++) {
				if (isdigit(str[i])) {
					numextract += str[i];
				} else {
					numextract += "0";
				}
			}

			intUser = std::stoi(numextract);
		} while (numextract.empty() || !isdigit(numextract[0]) || intUser > m_options.capacity() || intUser == 0);
		return intUser - 1;
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

	int menu::getIndex(std::string mOption) const {
		for (int i = 0; i < m_optionCount; ++i) {
			if (m_options[i] == mOption) {
				return i;
			}
		}
	}

}


