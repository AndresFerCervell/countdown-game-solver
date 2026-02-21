/**
*@file letters_bag.cpp
*@brief Implementación de la clase LettersBag
*/
#include "letters_bag.h"


LettersBag::LettersBag() : num_letras(0){}

LettersBag::LettersBag(const LettersSet &ls) {
    num_letras = 0;
    fill(ls);
}

void LettersBag::fill(const LettersSet &ls) {
    num_letras = 0;
    bolsa.clear();

    vector<char> extra = ls.GetLetrasConRepes();

    bolsa.insert(bolsa.end(), extra.begin(), extra.end());
    num_letras += extra.size();
}

int LettersBag::size() const {
    return num_letras;
}


bool LettersBag::empty() const {
    return (num_letras==0);
}

char LettersBag::get() {

    if (num_letras == 0) throw std::out_of_range("No hay elementos en la bolsa");

    int pos = rand() % num_letras;
    char elemento = bolsa[pos];

    bolsa[pos] = bolsa[num_letras - 1];

    num_letras--;

    return elemento;
}

string LettersBag::getMultiple(int n) {
    string resultado;
    for(int i = 0; i < n; ++i) {
        resultado+=get();
    }
    return resultado;
}

string LettersBag::toString() const {
    string resultado;
    for(char c : bolsa) {
        resultado += c;
    }
    return resultado;
}