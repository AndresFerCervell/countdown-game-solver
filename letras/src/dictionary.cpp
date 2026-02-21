/**
*@file dictionary.cpp
*@brief Implementación de la clase Dictionary
*
*Implementa un diccionario de palabras.
*/
#include "dictionary.h"
#include <algorithm>
#include <fstream>

using namespace std;

void minuscular(string& s) {
    for (char &c : s)
        c = tolower(c);
}

void enclavizar(string& s) {
    minuscular(s);
    sort(s.begin(), s.end());
}

Dictionary::Dictionary() : num_palabras(0) {}

int Dictionary::size() const {
    return num_palabras;
}

set<string> Dictionary::getPalabrasClave(const string& clave) const {
    string clave_copy = clave;
    enclavizar(clave_copy);

    if(!EsClave(clave_copy))
        throw std::invalid_argument("La clave no existe en el diccionario");

    return (datos.find(clave_copy))->second;
}

set<string> Dictionary::PalabrasLongitud(int longitud) const {
    set<string> resultado;

    // Recorremos el map
    for (const auto &entrada : datos) {
        if(entrada.first.length() == longitud) {
            //Insertamos todo el vector de palabras asociado a esa clave (que tiene la longitud deseada)
            resultado.insert(entrada.second.begin(), entrada.second.end());
        }
    }

    return resultado;
}

bool Dictionary::EsClave(const string& clave) const {
    string clave_copy = clave;
    enclavizar(clave_copy);
    return datos.find(clave) != datos.end();
}

bool Dictionary::Esta(const string &palabra) const {
    string clave = palabra;

    //la clave son las letras de la palabra ordenadas
    enclavizar(clave);

    auto it = datos.find(clave);

    //si no está la clave, no está la palabra
    if (it == datos.end())    return false;

    //buscamos dentro de la clave
    //declaramos el vector como referencia para evitar hacer una copia innecesaria
    const set<string> &asociadas = it->second;

    for (const string &p : asociadas){
        if (p == palabra)    return true;
    }

    //podría estar la clave, pero no por la palabra que buscamos
    return false;
}

int Dictionary::apariciones(char letra){
    int resultado = 0;
    letra = tolower(letra);

    //Usamos el iterador especial(solo recorre las claves que contienen la letra dada)
    for (iterator_letra it = begin_con_letra(letra); it != end_con_letra(letra); ++it) {
        string palabra = *((*it).begin());

        //Número de veces que aparece la letra en la palabra
        //(todas las palabras asociadas a esa clave tienen las mismas letras =>
        //letra aparece el mismo número de veces en cada una de ellas)
        int veces = count(palabra.begin(), palabra.end(), letra);

        //Sumamos al resultado el número de palabras asociadas a esa clave
        //multiplicado por el número de veces que aparece la letra en cada palabra de esa clave
        resultado+=((*it).size()*veces);
    }
    return resultado;
}

istream & operator>>(istream &is, Dictionary &D) {
    string palabra;
    D.datos.clear();
    D.num_palabras = 0;

    while (is >> palabra) {
        // clave = letras ordenadas
        minuscular(palabra);

        string clave = palabra;
        sort(clave.begin(), clave.end());

        D.datos[clave].insert(palabra);
        D.num_palabras++;
    }

    return is;
}

ostream & operator<<(ostream &os, const Dictionary &D) {

    for (const auto &p : D.datos) {
        for (const string &pal : p.second)
            os << pal << "\n";
    }

    return os;
}

// ITERATOR ESPECIAL

void Dictionary::iterator_letra::avanzar_siguiente() {
    while (it != it_end) {
        ++it;
        // comprobamos si la clave contiene la letra
        if (it->first.find(letra) != string::npos) return;
    }
}

Dictionary::iterator_letra::iterator_letra() = default;

Dictionary::iterator_letra::iterator_letra(
        map<string, set<string>>::iterator ini,
        map<string, set<string>>::iterator fin,
        char c) : it(ini), it_end(fin), letra(c)
{
    // va al primero que cumpla la condición
    avanzar_siguiente();
}


set<string> Dictionary::iterator_letra::operator*() const {
    return it->second;
}


Dictionary::iterator_letra & Dictionary::iterator_letra::operator++() {
    // si no cumple la condición sigue saltando
    avanzar_siguiente();

    return *this;
}

bool Dictionary::iterator_letra::operator==(const iterator_letra &other) const {
    return it == other.it;
}

bool Dictionary::iterator_letra::operator!=(const iterator_letra &other) const {
    return it != other.it;
}

Dictionary::iterator_letra Dictionary::begin_con_letra(char letra) {
    return iterator_letra(datos.begin(), datos.end(), letra);
}

Dictionary::iterator_letra Dictionary::end_con_letra(char letra) {
    // el end no filtra nada (letra es innecesario)
    return iterator_letra(datos.end(), datos.end(), letra);
}
