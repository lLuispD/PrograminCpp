#include <iostream>
#include <string>
std::string texto;
double op;


int main() {
	std::cout << "introduce 1+1\n";
	std::cin >> texto;
	op = std::stoi(texto);
	std::cout << op << std::endl;
	return 0;
}
