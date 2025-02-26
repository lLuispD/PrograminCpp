#pragma once

#include <vector> 

std::vector <std::string> FilterList = { "Filtro Paso Bajo", "Filtro Paso Alto" };
std::vector <std::string> CapMultList = { "pF" , "nF" , "uF" };
std::vector <std::string> ResMultList = { " " , "k" , "M"};
std::vector <std::string> FrecMultList = { "Hz" , "KHz" , "MHZ" , "GHz"};

const float valuesResistance[] = { 1 , 1.2 , 1.5 , 1.8 , 2.2 , 2.7 , 3.3 , 3.9 , 4.7 , 5.1 , 5.6 , 6.8 , 8.2 };

const float MlutResistances[] = {1 , 10 , 100 , 1000 , 10000 , 100000 , 1000000 };


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


 




constexpr auto PI = 3.14159265358979323846;   // pi;
float RHA = 0;
float RHB = 0;
float RH1 = 0;
float RH2 = 0;
float CH1 = 0;
float CH2 = 0;
float k;
float QualityFactor = 10;
float CutFrequency = 1;			 // CutFrequency = 1 / (2 * PI * sqrt(RH1 * CH1 * RH2 * CH2));
float tmp_producto = 0; // Variable temporal para almacenar  RH1 * CH1 * RH2 * CH2
float tmp_subproducto = 0; // Almacena los sub productos luego de empezar a dar valores

