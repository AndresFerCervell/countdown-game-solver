/**
*@file letters_set.cpp
*@brief Implementación de la clase LettersSet
*/
#include "letters_set.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#include "dictionary.h"

using namespace std;

LettersSet::LettersSet() = default;

LettersSet::LettersSet(const string& s) {
    for (char c : s) {
        insert(LetterInfo(tolower(c)));
    }
}

LettersSet::LettersSet(const string& s, const LettersSet& otro) {
    for (char c : s) {
        c = tolower(c);
        if (otro.count(c)) {
            insert(otro.getLetra(c));
        }
    }
}

int LettersSet::size() const {
    return datos.size();
}

void LettersSet::insert(const LetterInfo& l){
    //realmente solo se está comparando el caracter por estar así definido el set
    if (datos.find(l) == datos.end()) {
        datos.insert(l);

    }else {
        //se actualiza
        datos.erase(l);
        datos.insert(l);
    }
}

void LettersSet::erase(char c) {
    LetterInfo aux(c);

    //realmente solo se está buscando el caracter por estar así definido el set
    auto it = datos.find(aux);

    if (it != datos.end()) {
        datos.erase(it);
    }
}

bool LettersSet::count(char c) const {
    LetterInfo aux(c);

    return datos.find(aux) != datos.end();
}

LetterInfo LettersSet::getLetra(char c) const {
    LetterInfo aux(c);

    auto it = datos.find(aux);

    if (it != datos.end()) {
        return *it;
    }

    return aux;   // no existe la letra (frecuencia y puntuación 0)
}

int LettersSet::sumaPuntuaciones() const {
    int suma = 0;

    for (const auto &info : datos) {
        suma += info.puntuacion;
    }

    return suma;
}

int LettersSet::sumaPuntuaciones(const string& st) const {
    int suma = 0;

    for (char c : st) {
        suma += getLetra(c).puntuacion;
    }

    return suma;
}

vector<char> LettersSet::GetLetrasConRepes() const {
    vector<char> letras;

    for (const auto &info : datos) {
        int repes = info.cantidad;
        char letra = info.caracter;

        for (int i = 0; i < repes; ++i) {
            letras.push_back(letra);
        }
    }

    return letras;
}

vector<char> LettersSet::GetLetrasSinRepes() const {
    vector<char> letras;

    letras.reserve(datos.size());
    for (const auto &info : datos) {
        letras.push_back(info.caracter);
    }

    return letras;
}

void LettersSet::recalcularPuntos() {
    vector<int> frecuencias;
    frecuencias.reserve(datos.size());
    for (const auto &info : datos) {
        frecuencias.push_back(info.cantidad);
    }

    int max = *max_element(frecuencias.begin(), frecuencias.end());
    //int min = *min_element(frecuencias.begin(), frecuencias.end());

    vector<LetterInfo> nuevos;

    for (const auto &info : datos) {
        LetterInfo copy = info;

        int punt = 0;

        if (info.cantidad != 0) {
            punt = max / info.cantidad;
            if (punt > 10)  punt = 10;
        }

        /*
        double factor = double(info.cantidad - min) / double(max - min);
        punt = 10 - int(round(factor * 9));
        */

        copy.puntuacion = punt;

        nuevos.push_back(copy);
    }


    for (auto &l : nuevos) {
        //actualiza
        insert(l);
    }


}

string LettersSet::toString() const {
    string resultado;
    for (const auto &info : datos) {
        resultado += info.caracter;
    }
    return resultado;
}



istream& operator>>(istream &is, LettersSet &ls) {
    //vaciamos el set
    ls.datos.clear();

    string cabecera;
    // Leemos la cabecera del archivo para descartarla
    getline(is, cabecera);

    char caracter;
    int cantidad, puntuacion;

    while (is >> caracter >> cantidad >> puntuacion) {
        ls.insert(LetterInfo(caracter, cantidad, puntuacion));
    }

    return is;
}

ostream& operator<<(ostream &os, const LettersSet &ls) {
    os << "Letra Cantidad Puntos" << endl;

    for (const auto &info : ls.datos) {
        os << (char)toupper(info.caracter) << "\t" << info.cantidad << "\t" << info.puntuacion << endl;
    }

    return os;
}
