/**
*@file bolsa_letras.cpp
*@brief Programa principal para gestionar una bolsa de letras
*
*Dado un conjunto de letras y sus frecuencias, permite extraer un número
*determinado de letras al azar, que muestra en pantalla.
*/


#include <iostream>
#include <fstream>
#include <string>
#include "letters_set.h"
#include "letters_bag.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3) {
        cout << "Uso: ./bolsa_letras data/letras.txt num" << endl;
        return 1;
    }

    ifstream data(argv[1]);

    if(!data) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    // Inicializamos el generador de números aleatorios
    srand(time(NULL));

    LettersSet ls;
    data >> ls;
    LettersBag bag(ls);

    string resultado = bag.getMultiple(stoi(argv[2]));

    for(char c : resultado) {
        cout << c << endl;
    }

    return 0;
}