/**
 *@file dictionary.h
 *@brief Descripción del TDA dictionary
*/

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;

/*
@brief Convierte una cadena a minúsculas
@param s cadena a convertir
*/
void minuscular(string& s);

/*
@brief Convierte una cadena a minúsculas y la ordena
@param s cadena a convertir
*/
void enclavizar(string& s);

/**
 * @brief TDA Dictionary
 *
 * Almacena las palabras de un fichero de texto asociándolas a una clave (sus letras
 * ordenadas alfabéticamente.
 *
 * @details Guarda todo en minúscula.
 * @details Almacena claves (letras ordenadas alfabéticamente) a las que le
 * corresponden una serie de palabras.
 *
 * @invariant Tanto las claves como las palabras estarán siempre en minúscula.
 */
class Dictionary {
private:

    /**
    @brief Estructura principal del diccionario. A cada palabra se le asigna una
    clave, sus letras ordenadas, a la que se asocian todas las palabras
    del diccionario que la comparten
    */
    map<string, set<string>> datos;

    /**
    @brief Número de palabras
    */
    int num_palabras;

public:

    /**
    @brief Construye un diccionario vacío.
    */
    Dictionary();

    /**
    @brief Devuelve el número de palabras en el diccionario
    @return Número de palabras
    */
    int size() const;

    /**
    @brief Devuelve un vector con las palabras con la misma clave
    @pre La clave existe
    @throw std::invalid_argument Si la clave no existe
    @note Ordena la clave alfabéticamente
    @param clave Clave de las palabras que buscamos
    @return Set con palabras de igual clave
    */
    set<string> getPalabrasClave(const string& clave) const;

    /**
    @brief Obtiene todas las palabras del diccionario de una longitud dada
    @param longitud Longitud de las palabras de salida
    @return vector con las palabras de la longitud indicada
    */
    set<string> PalabrasLongitud(int longitud) const;

    /**
    @brief Indica si una clave está en el diccionario
    @note No es necesario que la clave esté ordenada, se ordena antes de buscarla
    @param clave clave a buscar
    @return true si está, false en caso contrario
    */
    bool EsClave(const string& clave) const;

    /**
    @brief Indica si una palabra está en el diccionario
    @param palabra Palabra a buscar
    @return true si está, false en caso contrario
    */
    bool Esta(const string &palabra) const;

    /**
    @brief Cuenta el número de apariciones de una letra en el diccionario
    @param letra para la que quieres saber el número apariciones
    @return numero de palabras que continen la letra
    */
    int apariciones(char letra);

    /**
    @brief Lee de un flujo de entrada un diccionario
    @param is flujo de entrada
    @param D diccionario donde se almacena lo leído
    @return flujo de entrada
    */
    friend istream & operator>>(istream &is, Dictionary &D);

    /**
    @brief Escribe en un flujo de salida un diccionario
    @param os flujo de salida
    @param D diccionario a escribir
    @return flujo de salida
    */
    friend ostream & operator<<(ostream &os, const Dictionary &D);

    /**
    @brief Iterador que recorre solo las claves que contienen una letra dada
    Ejemplo: si la letra es 'a', solo recorrerá las claves que contienen 'a'
    (y por tanto las palabras asociadas a esas claves también contienen 'a')
    */
    class iterator_letra {
    private:
        map<string, set<string>>::iterator it;
        map<string, set<string>>::iterator it_end;
        char letra{};

        /**
        @brief Función auxiliar que avanza el iterador al siguiente elemento
        que cumple la condición de contener la letra dada
        */
        void avanzar_siguiente();

    public:

        /**
        @brief Constructor por defecto
        */
        iterator_letra();

        /**
        @brief Constructor con parámetros
        @param ini iterador al inicio del mapa
        @param fin iterador al final del mapa
        @param c Letra que deben contener las palabras
        */
        iterator_letra(map<string, set<string>>::iterator ini,
                        map<string, set<string>>::iterator fin,
                        char c);

        /**
        @brief Devuelve el vector de palabras asociado a la clave actual
        */
        set<string> operator*() const;

        /**
        @brief Avanza el iterador al siguiente elemento con clave con dicha letra
        */
        iterator_letra & operator++();

        /**
        @brief Compara dos iteradores
        */
        bool operator==(const iterator_letra &other) const;

        /**
        @brief Compara dos iteradores
        */
        bool operator!=(const iterator_letra &other) const;
    };

    /**
    @brief Iterador filtrado al inicio para una letra dada
    @param letra Letra que deben contener las palabras
    */
    iterator_letra begin_con_letra(char letra);

    /**
    @brief Iterador filtrado al final para una letra dada
    */
    iterator_letra end_con_letra(char letra);
};

#endif
