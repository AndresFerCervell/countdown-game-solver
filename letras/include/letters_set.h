/**
 *@file letters_set.h
 *@brief Descripción del TDA LetterInfo
*/

#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra.
 *
 * @invariant Los caracteres siempre serán letras en minúscula.
 */

struct LetterInfo {
    char caracter;
    int cantidad;
    int puntuacion;

    // Constructor con 1 parámetro
    LetterInfo(char c)
        : caracter(tolower(c)), cantidad(0), puntuacion(0) {}

    // Constructor con 3 parámetros
    LetterInfo(char c, int cant, int punt)
        : caracter(tolower(c)), cantidad(cant), puntuacion(punt) {}

};

/**
@brief Functor de ordenación de LetterSet por carácter
*/
struct OrdenLetra {
    bool operator()(const LetterInfo &a, const LetterInfo &b) const {
        return a.caracter < b.caracter;
    }
};

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra. Los caracteres se ordenan alfabéticamente.
 */

#include <set>
#include <vector>


class LettersSet {
private:
    set<LetterInfo, OrdenLetra> datos;

public:
    /**
    @brief Construye un conjunto de letras vacío
    */
    LettersSet();

    /**
    @brief Construye un conjunto de letras a partir de un string
    @param s string a convertir
    */
    LettersSet(const string& s);

    /**
    @brief Copia de otro LetterSet únicamente los elementos del string
    @param s letras elegidas
    @param otro LetterSet a copiar
    */
    LettersSet(const string& s, const LettersSet& otro);

    /**
    @brief Devuelve el número de letras distintas en el conjunto
    @return número de letras
    */
    int size() const;

    /**
    @brief Inserta una letra en el conjunto si aún no existía, si sí, lo actualiza.
    @param l letra a insertar
    */
    void insert(const LetterInfo& l);

    /**
    @brief Borra una letra del conjunto
    @param c carácter de la letra a borrar
    */
    void erase(char c);

    /**
    @brief Indica si una letra está en el conjunto
    @param c carácter a buscar
    @return true si está, false en caso contrario
    */
    bool count(char c) const;

    /**
    @brief Devuelve la información de una letra
    @param c carácter de la letra
    @return letra correspondiente. Si no existe, se devuelve una letra con cantidad y puntuación 0
    */
    LetterInfo getLetra(char c) const;

    /**
    @brief Devuelve la suma de las puntuaciones de todas las letras del set
    @return suma de las puntuaciones
    */
    int sumaPuntuaciones() const;

    /**
    @brief Devuelve la suma de las puntuaciones de todas las letras del string
    según las puntuaciones del LetterSet
    @return suma de las puntuaciones
    */
    int sumaPuntuaciones(const string& st) const;

    /**
    @brief Devuelve todos los caracteres de las letras del conjunto tantas veces como su cantidad
    @return vector con las letras, con repetidas
    Ej: si el conjunto tiene A(3), B(2), C(1), devuelve {A,A,A,B,B,C}
    */
    vector<char> GetLetrasConRepes() const;

    /**
     @brief Devuelve todos los caracteres de las letras del conjunto, una vez cada una
     @return vector con las letras, sin repetidas
     Ej: si el conjunto tiene A(3), B(2), C(1), devuelve {A,B,C}
     */
    vector<char> GetLetrasSinRepes() const;


    /**
    @brief Recalcula los puntos (1-10) de cada letra en función de su cantidad
    @note Entendemos que la letra más repetida tiene puntuación 1 y que cada
    puntuación significa que esa letra aparece tantas veces menos en el diccionario
    que la máxima, siendo, por tanto, tantas veces más difícil generar una palabra que
    la contenga.
    @note Se propone (comentada) otra opción de cálculo mediante la siguiente
    fórmula: 10 - round( (cantidad - min) / (max - min) * 9 )
    */
    void recalcularPuntos();

    /**
    @brief transforma el LetterSet en una cadena de caracteres
    @return cadena de caracteres correspondiente
    */
    string toString() const;

    /**
    @brief Lee un conjunto de letras de un flujo de entrada
    @param is flujo de entrada
    @param C conjunto donde se almacena lo leído
    @return flujo de entrada
    */
    friend istream & operator>>(istream &is, LettersSet &C);

    /**
    @brief Escribe un conjunto de letras en un flujo de salida
    @param os flujo de salida
    @param C conjunto que se escribe
    @return flujo de salida
    */
    friend ostream & operator<<(ostream &os, const LettersSet &C);

};

#endif
