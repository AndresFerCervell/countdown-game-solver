/**
 *@file letters_bag.h
 *@brief Descripción del TDA LettersBag
*/
#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__


#include <vector>
#include "letters_set.h"

using namespace std;

/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */
class LettersBag {
private:
    vector<char> bolsa;
    int num_letras;

public:
    /**
    @brief Construye una bolsa vacía
    */
    LettersBag();

    /**
    @brief Construye una bolsa a partir de un conjunto de letras
    @param ls conjunto de letras
    */
    LettersBag(const LettersSet &ls);

    /**
    @brief Rellena la bolsa a partir de un conjunto de letras, borrando el contenido anterior
    @param ls conjunto de letras
    */
    void fill(const LettersSet &ls);

    /**
    @brief Devuelve el número de fichas en la bolsa
    @return tamaño de la bolsa
    */
    int size() const;

    /**
    @brief Indica si la bolsa está vacía
    @return true si está vacía, false en caso contrario
    */
    bool empty() const;

    /**
    @brief Extrae un caracter aleatorio de la bolsa
    @throw std::out_of_range si no quedan elementos que extraer
    @return caracter extraído
    */
    char get();

    /**
    @brief Extrae el número indicado de caracteres aleatoriamente de la bolsa
    @param n número de elementos a extraer
    @return vector de caracteres extraídos
    */
    string getMultiple(int n);

    /**
    @brief Transforma la bolsa en una cadena de caracteres
    @return cadena de caracteres correspondiente
    */
    string toString() const;
};

#endif
