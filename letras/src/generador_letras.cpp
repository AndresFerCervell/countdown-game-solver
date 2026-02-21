/**
@file generador_letras.cpp
@brief Programa principal para generar un conjunto de letras

*Dado un diccionario, genera un conjunto de letras con la frecuencia
*de aparición de cada letra en el diccionario y calcula los puntos de cada letra
*en función de su frecuencia. Finalmente, muestra el conjunto de letras por pantalla.
*/
#include <iostream>
#include <fstream>
#include <string>
#include "letters_set.h"
#include "dictionary.h"

using namespace std;

int main(int argc, char *argv[])
{
    const string ABECEDARIO = "abcdefghijklmnopqrstuvwxyz";

    if(argc != 2) {
        cout << "Uso: ./generador_letras data/diccionario.txt" << endl;
        return 1;
    }

    ifstream diccionario(argv[1]);

    if(!diccionario) {
        cout << "Error al abrir el archivo de diccionario" << endl;
        return 1;
    }


    Dictionary dic;
    diccionario >> dic;

    LettersSet ls;

    for(char c : ABECEDARIO) {
        ls.insert(LetterInfo(c, dic.apariciones(c), 0));
    }

    ls.recalcularPuntos();

    cout << ls;

    return 0;
}