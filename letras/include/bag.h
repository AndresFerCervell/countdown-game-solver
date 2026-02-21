/**
 *@file bag.h
 *@brief Descripción del TDA Bag
*/

#ifndef __BAG_H__
#define __BAG_H__

#include <vector>
#include <cstdlib>
using namespace std;

/**
 *  \brief TDA Bag
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */

template <class T>
class Bag {

private:
    vector<T> datos;  ///< Elementos almacenados en la bolsa
    int num_elementos;

public:

    /**
     * @brief Constructor por defecto (bolsa vacía)
     */
    Bag() : num_elementos(0) {}

    /**
     * @brief Vacía una bolsa
     */
    void clear() {
        datos.clear();
        num_elementos = 0;
    }

    /**
     * @brief Inserta un elemento en la bolsa
     * @param elemento valor a añadir
     */
    void add(const T &elemento) {
        datos.push_back(elemento);
        num_elementos++;
    }

    /**
     * @brief Devuelve cuántos elementos hay en la bolsa
     * @return número de elementos
     */
    int size() const {
        return num_elementos;
    }

    /**
     * @brief Extrae un elemento aleatorio sin reemplazamiento
     * @throw std::out_of_range si no quedan elementos que extraer
     * @return elemento extraído
     */
    T get() {
        if (num_elementos == 0) throw std::out_of_range("No hay elementos en la bolsa");

        int pos = rand() % num_elementos;
        T elemento = datos[pos];

        datos[pos] = datos[num_elementos - 1];
        num_elementos--;

        return elemento;
    }
};

#endif