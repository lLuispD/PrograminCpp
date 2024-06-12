

#//********************************************* 

#include <iostream>
#include <time.h>
#include <conio.h>




void imprimir(std::string texto);  
void imprimir(std::string texto, int valor);
int consultar(std::string consulta);
void inicializar();
int aleatorio(int minimo, int rango);

// Funcion principal 
int main() {
char again = 1;

do {
inicializar();
int valor = aleatorio(1, 100);
int ingreso;
int i = 0;

system("cls");
imprimir("Bienvenido a \"Adivina el numero\" \nEl numero esta entre 0 y 100\n");
do {
//intentos
i = i + 1; 
ingreso = consultar("Ingrese un numero  ");
if (ingreso > valor) {
    imprimir("El numero es menor\n");
}else if (ingreso < valor) {
    imprimir("El numero es mayor\n");
}
} while (ingreso != valor);

imprimir("Felicidades, has adivinado el numero. el numero fue: ", valor);
std::cout  << std::endl;
std::cout << "Numero de intentos: " << i << std::endl << std::endl;

imprimir("¿Desea volver a jugar?");
imprimir("presione '1' o esctriba 'true' para reiniciar el juego,");
imprimir("si no, escriba cualquier otra cosa");     
    std::cin >> again;

} while (again != 1);
system("cls");
imprimir("Gracias por jugar c:");

return 0;
}
//------------| 
// FUNCIONES  | 
// -----------| 

// Funcion imprimir en pantalla 
void imprimir(std::string texto) {
    std::cout << texto << std::endl;
}

// Sobrecarga de funciones 
void imprimir(std::string texto, int valor) {
   
    std::cout << texto << " " << valor << std::endl;
}

// Funcion consultar 
int consultar(std::string consulta) {
    int numero;
    std::cout << consulta << " ";
    std::cin >> numero;
    return numero;
}

// Funcion inicializar 
void inicializar() {
    srand(time(NULL));
}

// Funcion valor aleatorio 
int aleatorio(int minimo, int rango){
    int valor = minimo + rand() % rango;
    return valor;
}

