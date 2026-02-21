/**
*@file bolsa.cpp
*@brief Programa principal para gestionar una bolsa genérica
*
*Permite crear una bolsa de elementos de tipo entero o cadena de caracteres,
*(dependiendo del primer argumento de la línea de comandos, I para enteros y C para
*cadenas), añadirles elementos y extraerlos aleatoriamente hasta que la bolsa quede vacía
*/
#include <iostream>
#include <string>
#include "bag.h"

using namespace std;

int main(int argc, char *argv[])
{
  // Inicializamos el generador de números aleatorios
  srand(time(NULL));

  // Comprobamos número de argumentos
  if(argc < 2) {
    cout << "Uso: ./bolsa C|I elem1 elem2 ..." << endl;
    return 1;
  }

  // Creamos una bolsa de caracteres si el primer argumento es una C
  if (argv[1][0] == 'C') {
    Bag<string> bag;

    // Metemos todos los argumentos en la bolsa
    for (int i = 2; i < argc; ++i) {
      bag.add(argv[i]);
    }

    // Los extraemos aleatoriamente y los imprimimos hasta que se nos quede la
    // bolsa vacía
    while (bag.size() > 0) {
      cout << bag.get() << endl;
    }

    // Creamos una bolsa de enteros si el primer argumento es una I
  } else if (argv[1][0] == 'I') {
    Bag<int> bag;

    // Metemos todos los argumentos en la bolsa
    for (int i = 2; i < argc; ++i) {
      bag.add(stoi(argv[i]));
    }

    // Los extraemos aleatoriamente y los imprimimos hasta que se nos quede la
    // bolsa vacía
    while (bag.size() > 0) {
      cout << bag.get() << endl;
    }
  }

  return 0;
}
