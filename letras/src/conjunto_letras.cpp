/**
*.@file conjunto_letras.cpp
*.@brief Programa principal para mostrar un conjunto de letras
*
*.Dado un archivo con la información de un conjunto de letras, muestra
*.por pantalla dicha información.
*/
#include <iostream>
#include <fstream>
#include "letters_set.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2) {
        cout << "Uso: ./conjunto_letras data/letras.txt" << endl;
        return 1;
    }

    ifstream data(argv[1]);

    if(!data) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    LettersSet ls;
    data >> ls;

    cout << ls;


    return 0;
}