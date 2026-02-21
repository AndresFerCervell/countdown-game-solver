/**
*@file cantidad_letras.cpp
*@brief Programa principal para calcular la cantidad de letras en un diccionario
*
*Dado un diccionario y un conjunto de letras, calcula cuántas veces aparece
*cada letra del conjunto en el diccionario y actualiza la información de las letras
*con dicha cantidad. Finalmente, calcula los puntos de cada letra en función de su frecuencia
*en el diccionario y muestra la información actualizada de las letras por pantalla.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include "letters_set.h"
#include "dictionary.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3) {
        cout << "Uso: ./cantidad_letras data/diccionario.txt data/letras.txt" << endl;
        return 1;
    }

    ifstream diccionario(argv[1]);

    if(!diccionario) {
        cout << "Error al abrir el archivo de diccionario" << endl;
        return 1;
    }

    ifstream dataLetras(argv[2]);

    if(!dataLetras) {
        cout << "Error al abrir el archivo de letras" << endl;
        return 1;
    }


    Dictionary dic;
    diccionario >> dic;

    LettersSet ls;
    dataLetras >> ls;

    vector<char> letras = ls.GetLetrasSinRepes();

    for(char c : letras) {
        ls.insert(LetterInfo(c, dic.apariciones(c), 0));
    }

    ls.recalcularPuntos();

    cout << ls;

    return 0;
}