#pragma once

#include <random>
#include <vector> 

std::vector <std::string> FilterList = { "Filtro Paso Bajo", "Filtro Paso Alto" };
std::vector <std::string> CapMultList = { "pF" , "nF" , "uF" };
std::vector <std::string> ResMultList = { " " , "k" , "M"};
std::vector <std::string> FrecMultList = { "Hz" , "KHz" , "MHZ" , "GHz"};

const float valuesResistance[] = { 1.f , 1.2f , 1.5f , 1.8f , 2.2f , 2.7f , 3.3f , 3.9f , 4.7f , 5.1f , 5.6f , 6.8f , 8.2f };
const float MultResistances[] = {1.f , 10.f , 100.f , 1000.f , 10000.f , 100000.f , 1000000.f };

const float valuesCapacitance[] = { 1.f, 1.5f, 2.2f, 3.3f, 4.7f, 6.8f, 10.f, 15.f, 22.f, 33.f, 47.f, 68.f };
const float MultCapacitance[] = { 1e-12f, 1e-9f, 1e-6f };

	// Genera un número entero aleatorio en el rango [min, max]
	int randomNumber(int min, int max) {
		static std::random_device rd;  // Fuente de semilla
		static std::mt19937 gen(rd()); // Generador Mersenne Twister
		std::uniform_int_distribution<> dis(min, max);
		int value = dis(gen);
		return value;
	}


namespace dataF {
	constexpr auto PI = 3.14159265358979323846;   // pi;
	float RA = 1.f;
	float RB = 0;
	float R1 = 0;
	float R2 = 0;
	float C1 = 0;
	float C2 = 0;
	float Gain = 1.f;
	float QualityFactor = 1.f;
	float CutFrequency = 1.f;			 // CutFrequency = 1 / (2 * PI * sqrt(RH1 * CH1 * RH2 * CH2));
	float tmp_producto = 0; // Variable temporal para almacenar  RH1 * CH1 * RH2 * CH2
	float tmp_subproducto = 0; // Almacena los sub productos luego de empezar a dar valores


	float createResistance() {
		float valR = valuesResistance[randomNumber(0, 12)];
		float valMul = MultResistances[randomNumber(0, 6)];
		return (valR * valMul);
	}
	
	float createCapacitance() {
		float valC = valuesCapacitance[randomNumber(0, 11)] ;
		float valMul = MultCapacitance[randomNumber(0, 2)];
		return (valC * valMul);
	}


}

/*
 
	std::cin >> k;

	std::cout << "\Escriba un valor para RHA: ";


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


 


