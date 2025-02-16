/*	Este programa sirve para diseniar filtros Butterworth de segundo orden
* Se deben estableces en orden
* Ganancia
* Frecuencia de corte
* Capacitores
* Resistencias
* La ultima resistencia se define auntomaticamente
*/
	/*

#include "main.hpp"
#include <iostream>
#include "mul&sub.hpp"

int main() {
	std::cout << "\Escriba una valor para la ganancia: ";
	std::cin >> k;


	std::cout << "\Escriba un valor para RHA: ";
	std::cin >> RHA;
	RHB = (k - 1) * RHA;
	
	std::cout << "\Escriba un valor para la frecuencia de corte: ";
	std::cin >> CutFrequency;
	tmp_producto = 1 /((2 * PI * CutFrequency) * (2 * PI * CutFrequency));
	
	std::cout << "\el producto de CH1 * CH2 * RH1 *  RH2  = " << tmp_producto << "por favor introduzca el valor para CH1 ";
	std::cin >> CH1;
	tmp_subproducto = tmp_producto / CH1;

	std::cout << "\el producto de CH2 * RH1 *  RH2 = " << tmp_subproducto << "por favor introduzca el valor para CH2";
	std::cin >> CH2;
	tmp_subproducto = tmp_subproducto / CH2;
	std::cout << "\el producto de RH1 *  RH2 = " << tmp_subproducto << "por favor introduzca el valor para RH1 ";
	std::cin >> RH1;
	if (RH1 * (CH1 + CH2) == 0) {
		std::cout << "Error";
		return 1;
	}
	RH2 = tmp_subproducto / RH1;
	std::cout << "\el valor para RH2 es " << RH2 ;



	

	
	 //QualityFactor = (2 * PI * sqrt(RH1 * CH1 * RH2 * CH2)) / ( ( RH2 * CH2 ) * ( 1 - k) + RH1 * ( CH1 + CH2 ) );

	

	return 0;
}
	*/ 

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>



/*

float procesarNumeroConUnidad(const std::string& input) {
    // Definir los múltiplos y submúltiplos más comunes
    std::unordered_map<char, float> unidades = {
        {'T', 1e12},    // tera
        {'G', 1e9},     // giga
        {'M', 1e6},     // mega
        {'k', 1e3},     // kilo
        {' ', 1e0}
        {'m',1e-3}      // mili
        {'u', 1e-6},    // micro
        {'n', 1e-9},    // nano
        {'p', 1e-12},   // pico
    };

    // Separar la parte numérica y la unidad
    size_t pos = input.find_first_not_of("0123456789.");
    if (pos == std::string::npos ) {
        throw std::invalid_argument("Error al leer el valor");
    }

    std::string numStr = input.substr(0, pos);  // Parte numérica
    char unidad = input[pos];                   // Letra que representa la unidad

    // Convertir la parte numérica a float
    float numero = std::stof(numStr);

    // Verificar si la unidad está en el mapa
    if (unidades.find(unidad) != unidades.end()) {
        // Multiplicar el número por el factor correspondiente
        return numero * unidades[unidad];
    }
    else {
        throw std::invalid_argument("Unidad no reconocida.");
    }
}
*/ 

 
}
