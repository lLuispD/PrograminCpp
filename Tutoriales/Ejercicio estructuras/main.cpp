
//Estructuras
/*Ejercicio 2: Hacer una estructura llamada alumno, en la cual se
tendrán los siguientes Campos:
	-Nombre
	-Edad
	-Promedio
Pedir datos al usuario para 3 alumnos, comprobar cuál de los 3 tiene el mejor
promedio y posteriormente imprimir los datos del alumno.*/

#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;

struct alumno {
	char nombre[30];
	int edad;
	float promedio;
};
//Declaracion de variables de la estructura

int main() {
	system("title Alunmos");
	setlocale(LC_ALL, "esp");
	int n;
	struct alumno alumno1[200];

	cout << "Digite la cantidad de alumnos: ";
	cin >> n;
	for (int i = 0; i < n; i++) {

		cout << "\nAlumno [" << i + 1 << "]: " << endl;
		cout << "Nombre:  ";
		cin.ignore();
		cin.getline(alumno1[i].nombre, 40, '\n');
		cout << "Edad: ";
		cin >> alumno1[i].edad;
		cout << "Promedio: ";
		cin >> alumno1[i].promedio;
		cin.ignore();
		system("cls");
	}
	//Mostrar datos
	cout << "\Datos registrados:" << endl;
	for (int i = 0; i < n; i++) {

		cout << "\nAlumno [" << i + 1 << "]..." << endl;
		cout << "Nombre: " << alumno1[i].nombre << endl;
		cout << "Edad: " << alumno1[i].edad << endl;
		cout << "Promedio: " << alumno1[i].promedio << endl;
	}

	//Algoritmo para determinar el mayor de los datos
	float mayor;
	mayor = alumno1[0].promedio;
	for (int i = 0; i < n; i++) {
		if (alumno1[i].promedio > mayor) {
			mayor = alumno1[i].promedio;
		}
	}
	char a;
	cout << "\n pulse una letra, luego intro para ver el mejor promedio...\n";
	cin >> a;
	system("cls");
	cout << "\nEl mejor promedio es: " << mayor << endl;

	return 0;
}