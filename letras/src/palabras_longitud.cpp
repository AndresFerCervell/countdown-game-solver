/**
*@file palabras_longitud.cpp
*@brief Programa principal para calcular las palabras de un diccionario
*
*que tienen una longitud dada.
*/
#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3) {
        cout << "Uso: ./palabras_longitud data/diccionario.txt num" << endl;
        return 1;
    }

    ifstream diccionario(argv[1]);

    if(!diccionario) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    Dictionary dic;
    diccionario >> dic;

    set<string> palabrasLongitud = dic.PalabrasLongitud(stoi(argv[2]));

    for(const string& p : palabrasLongitud) {
        cout << p << endl;
    }

    return 0;
}