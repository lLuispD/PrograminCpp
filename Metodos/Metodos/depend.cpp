/*
	En esta parte se realiza la definicion de las funciones
	Aqui se incluyen las librerias necesarias para ejecutar el programa + el hpp del presente codigo
*/

#include "depend.hpp"
#include <iostream>
#include <math.h>
#include <conio.h>
#include <thread>
#include <chrono>

int iter = 1;
char option;
bool shwiter = false;  
int  special = 0;

void prositer() {
	
	std::cout << "ingrese el numero de iteraciones \n";
	std::cin >> iter;
	shwiter:
	std::cout << "Desea mostrar el resultado por cada iteracion (si = Y / no = N) \n";
	option = _getch();
	if (option == 'Y' || option == 'y') {
		shwiter = true;
	}	else if (option == 'N' || option == 'n') {
		shwiter = false;
	} else goto shwiter;

}


void menu() {
	system("cls");
	std::cout << "========== MENU ==========\n";
	std::cout << "[1] Ecuaciones no lineales \n";
	std::cout << "[2] Diferenciacion e integracion \n";
	std::cout << "[3] Ecuaciones diferenciales ordinarias \n";
	std::cout << "[4] Salir \n";

}

void subM1() {
	system("cls");
	std::cout << "========== Ecuaciones no lineales ==========\n";
	std::cout << "[1] Punto fijo \n";
	std::cout << "[2] Biseccion \n";
	std::cout << "[3] Newton - Raphson \n";
	std::cout << "[4] Secante \n";
	std::cout << "[5] Regla falsa \n";
	std::cout << "[6] Regresar \n";
}

void subM1A() { 
	system("cls");
	std::cout << "========== Punto fijo ==========\n";
	std::cout << "[1] Por implementar \n";
	std::cout << "[2] End \n";
	std::cout << "[3] Regresar \n";

}

void subM2(){
	system("cls");
	std::cout << "========== Diferenciacion e integracion ==========\n";
	std::cout << "[1] Por implementar\n";
	std::cout << "[2] Regresar \n";

}
void subM3() {
	system("cls");
	std::cout << "========== Ecuaciones diferenciales ordinarias ==========\n";
	std::cout << "[1] Por implementar\n";
	std::cout << "[2] Regresar \n";

}

void especial() {
	if (special > 3) {
		system("cls\n");
		std::cout << "oe que chucha, eres especial o que?\n";
		special = 0;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		
	}
	else special++;

}

