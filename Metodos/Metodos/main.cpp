
#include "depend.hpp"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <conio.h>


double var[10];

static double fpura(double x) {
	// Funcion sin despejar
	return (
		
		cos(x + 2) + pow(x, sin(x - 2)) -2				// -3 + x + cos( + 3 * x) 
);}

static double fun(double x) {
	// Funcion despejada
	return (
		3 - cos( pow(x , sin(x)) + 3 * x) 
);}
static double dxfun(double x) {
	// Funcion derivada
	return  (
		-sin(x + 2) + 3 * pow(x,2)
);}


int main() {
menu:
	std::cout << std::fixed << std::setprecision(30);
	menu();
	option = _getch();
	
	if		(option == '1') {															// [1] Ecuaciones no lineales  
	subM1:
		subM1();
		option = _getch();									
		if		(option == '1') {								// 
		subM1A:
			subM1A();
			option = _getch();
			if		(option == '1') {							// Met Punto fijo
				system("Cls");
				std::cout << "ingrese el valor inicial \n";
				std::cin >> var[0];
				prositer();
				for ( int i = 0; i < iter; i++ )	{
					var[0] = fun(var[0]);
					if (shwiter) std::cout << "x_" << (i + 1) << " = " << var[0] << std::endl;
					if (!shwiter && i == (iter - 1))std::cout << "x_" << (i + 1) << " = " << var[0] << std::endl;
					
				}
				system("\n Pause");
				goto subM1A;
			} 
			else if (option == '2'){
				std::cout << "end\n";
				system("\n pause");

			} 
			else if (option == '3') {						// Regresar
				goto subM1;
			}else goto subM1A;


			
			
			
		}
		else if (option == '2') {

			system("Cls");
			std::cout << "ingrese el valor inicial \n x_0 = ";
			std::cin >> var[1];
			std::cout << "ingrese el valor inicial \n x_1 = ";
			std::cin >> var[2];
			prositer();

			fpura(var[0]);
			for (int i = 0; i < iter; i++) {
				enum varr { x = 0, a = 1, b = 2 };

				var[x] = ((var[a] + var[b]) / 2);

				//std::cout << "a =  " << var[a] << std::endl;
				if (shwiter) std::cout << "x =  " << (i + 1) << " : " << var[x] << std::endl;
				if (!shwiter && i == (iter - 1))std::cout << "x_" << (i + 1) << " = " << var[x] << std::endl;
				//std::cout << "b =  " << var[b] << std::endl << std::endl;

				//std::cout << "f(a) * f(x):  " << fpura(var[a]) << " * " << fpura(var[x]) << ") = " << (fpura(var[a]) * (fpura(var[x])) ) << std::endl;
				//std::cout << "f(x) * f(b):  " <<fpura(var[x]) << " * " << fpura(var[b]) << ") = " << (fpura(var[x]) * (fpura(var[b]))) << std::endl;

				if ((fpura(var[a]) * (fpura(var[x]))) < 0) {
					var[b] = var[x];
					//std::cout <<" b = x " << std::endl;
				}
				else if ((fpura(var[x]) * (fpura(var[b]))) < 0) {
					var[a] = var[x];
					//std::cout << " a = x " << std::endl;
				}
				else return 1;

			}

			system("\n Pause");
			goto subM1;
		}
		else if (option == '3') {

			system("Cls");
			std::cout << "ingrese el valor inicial \n x_0 = ";
			std::cin >> var[0];
			prositer();
			for (int i = 0; i < iter; i++) {
				var[0 + 1] = var[0] - (fpura(var[0]) / dxfun(var[0]));
				if (shwiter) std::cout << "x =  " << (i + 1) << " : " << var[1] << std::endl;
				if (!shwiter && i == (iter - 1))std::cout << "x_" << (i + 1) << " = " << var[1] << std::endl;
				var[0] = var[1];
			}
			system("\n Pause");
			goto subM1;
		}
		else if (option == '4') {							// Secante

			system("Cls");
			std::cout << "ingrese el valor inicial \n x_0 = ";
			std::cin >> var[0];
			std::cout << "ingrese el valor inicial \n x_1 = ";
			std::cin >> var[1];
			prositer();
			 
			for (int i = 0; i < iter; i++) {
				enum varr { x_0 = 0, x_1 = 1, x_2 = 2 };			// xi = x_i | x_1 = x_i-1 |x_2 = x_i-2

				var[x_2] = (var[x_1] * fpura(var[x_0]) - var[x_0] * fpura(var[x_1])) /
							(fpura(var[x_0]) - fpura(var[x_1])); 

				//std::cout << "a =  " << var[a] << std::endl;
				if (shwiter) std::cout << "x =  " << (i + 2) << " : " << var[x_2] << std::endl;
				if (!shwiter && i == (iter - 1))std::cout << "x_" << (i + 1) << " = " << var[x_2] << std::endl;
				//std::cout << "b =  " << var[b] << std::endl << std::endl;
				var[x_0] = var[x_1];
				var[x_1] = var[x_2];

			}

			system("\n Pause");
			goto subM1;
		}
		else if (option == '5') {							// Regresar
			goto menu;
		}
		else  goto subM1;
		
	} 
	else if (option == '2') {															// [2] Diferenciacion e integracion
	subM2:
		subM2();
		option = _getch();
		if (option == '1') {

		}
		else if (option == '2') {
			goto menu;
		}else goto subM2;
	}
	else if (option == '3') {															// [3] Ecuaciones diferenciales ordinarias
	subM3:
		subM3();
		option = _getch();
		if (option == '1') {

		}
		else if (option == '2') {
			goto menu;
		}
		else goto subM3;
	}
	else if (option == '4') {								// Salir
		return 0;
	}
	else  goto menu;



	return 0;
}


