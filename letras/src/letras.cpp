/**
*@file letras.cpp
*@brief Programa principal para el juego de letras
*
*Permite jugar al juego de letras en modo longitud o puntuación,
*generando un conjunto de letras aleatorias a partir de una bolsa
*y comprobando las respuestas del usuario frente a un diccionario.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"

using namespace std;

/**
@brief Función auxiliar que devuelve un set de strings con todas las combinaciones
de letras distintas de tamaño k que se pueden formar a partir de un string dado.
@param letras string de donde sacar combinaciones
@param k tamaño de las combinaciones
Ejemplo de funcionamiento:
string letras = "abc"; int k = 2;
Devuelve el set {"ab", "ac", "bc"}
*/
set<string> combinacionesNumero(const string &letras, int k) {
    int size = letras.size();
    set<string> resultado;

    //usaremos MASKs

    int total = 1 << size; // 2^size combinaciones

    for (int mask = 1; mask < total; mask++) { // empieza en 1
        string s;
        for (int i = 0; i < size; i++) {
            if (mask & (1 << i))  // si el bit i está activo
                s.push_back(letras[i]);
        }

        sort(s.begin(), s.end());
        if (s.size() == k)
            resultado.insert(s);
    }

    return resultado;
}

/**
 * @brief struct que almacena un string y una puntuación que se le asigna
 */
struct str_puntuacion {
    string st;      /**< Cadena a la que se asocia una puntuación */
    int suma_punt;  /**< Puntuación asociada a la cadena */

    /**
     * @brief Constructor con argumentos
     * @note std::move evita una copia innecesaria
     */
    str_puntuacion(string  st, int suma) : st(std::move(st)), suma_punt(suma) {}

    /**
     * @brief Operador < en función de la puntuación
     * @note Servirá para ordenar un set de str_puntuacion de mayor a menor puntuación asociada
     */
    bool operator<(const str_puntuacion &otro) const {
        if (suma_punt != otro.suma_punt)
            return suma_punt > otro.suma_punt;
        return st < otro.st;
    }
};

/**
@brief Función auxiliar que devuelve un set de strings con todas las combinaciones
de letras distintas, ordenadas por puntuación, que se pueden formar a partir de un LetterSet dado.
@param ls LetterSet de donde sacar las combinaciones
*/
set<str_puntuacion> combinacionesGanadoras(const LettersSet &ls, const string &disponibles) {
    set<str_puntuacion> combinaciones;

    int size = disponibles.size();

    //usaremos MASKs

    int total = 1 << size; // 2^size combinaciones

    for (int mask = 1; mask < total; mask++) { // empieza en 1
        string new_st;
        for (int i = 0; i < size; i++) {
            if (mask & (1 << i))  // si el bit i está activo
                new_st.push_back(disponibles[i]);
        }

        sort(new_st.begin(), new_st.end());

        str_puntuacion new_st_punt(new_st, ls.sumaPuntuaciones(new_st));
        combinaciones.insert(new_st_punt);
    }

    return combinaciones;

}

/**
@brief Función auxiliar que devuelve las soluciones óptimas para el juego en modo L y
su longitud dado un diccionario y un string de caracteres disponibles.
@param dic Diccionario de entre donde coger palabras
@param disponibles string de letras que pueden usarse
@param longitud longitud de las soluciones óptimas. Parámetro de salida
*/
vector<string> modoL(const Dictionary &dic, const string &disponibles, int &longitud) {
    vector<string> soluciones_optimas;

    int num = disponibles.size();

    //buscamos de mayor a menor longitud
    for(longitud=num; longitud>=1; --longitud) {
        set<string> combinaciones = combinacionesNumero(disponibles, longitud);
        for(const string& p : combinaciones) {
            //De entre las combinaciones de longitud 'longitud', buscamos las que estén en el diccionario
            if(dic.EsClave(p)) {
                //Si la clave existe, añadimos todas las palabras asociadas a la solución óptima
                set<string> aniadir = dic.getPalabrasClave(p);
                soluciones_optimas.insert(soluciones_optimas.end(), aniadir.begin(), aniadir.end());
            }
        }
        //Si ya hemos encontrado soluciones óptimas, salimos del bucle
        if(!soluciones_optimas.empty()) {
            break;
        }
    }
    return soluciones_optimas;
}

/**
@brief Función auxiliar que devuelve las soluciones óptimas para el juego en modo P y
su puntuación dado un diccionario, un LetterSet y un string de caracteres disponibles.
@param dic Diccionario de entre donde coger palabras.
@param ls LetterSet donde se corresponden caracteres con puntuaciones.
@param disponibles string de letras que pueden usarse.
@param punt puntuación de las soluciones óptimas. Parámetro de salida
*/
vector<string> modoP(const Dictionary &dic, const LettersSet &ls, const string &disponibles, int &punt) {
    vector<string> soluciones_optimas;  //Resultado
    LettersSet ls_disponibles(disponibles, ls); //LetterSet con las letras disponibles y sus puntuaciones

    set<str_puntuacion> combinaciones = combinacionesGanadoras(ls_disponibles, disponibles); //combinaciones ordenadas por puntuación
    punt = combinaciones.begin()->suma_punt;    //puntuación máxima

    bool encontrado = false;
    //Recorremos las combinaciones ordenadas por puntuación
    for(const str_puntuacion& p : combinaciones) {
        //Si la puntuación de la combinación actual es menor que la máxima y ya hemos encontrado
        //alguna solución óptima, salimos del bucle. Si no es así, actualizamos la puntuación máxima
        //Esto es, porque aunque ya hayamos encontrado soluciones óptimas, puede que haya más con la misma puntuación
        if (p.suma_punt != punt) {
            if (encontrado) {
                break;
            }
            //Actualizamos la puntuación máxima
            punt = p.suma_punt;
        }
        string clave = p.st;

        //De entre las combinaciones de máxima puntuación, buscamos las que estén en el diccionario
        if(dic.EsClave(clave)) {
            set<string> aniadir = dic.getPalabrasClave(clave);
            soluciones_optimas.insert(soluciones_optimas.end(), aniadir.begin(), aniadir.end());
            encontrado = true;
        }
    }

    return soluciones_optimas;
}

/**
@brief Función auxiliar que comprueba si es válida la respuesta dada por el usuario,
comprobando que se hayan usado únicamente las letras disponibles y que exista en el
diccionario
@param respuesta respuesta del usuario a comprobar
@param disponibles string de letras que pueden usarse.
@param dic Diccionario de entre donde coger palabras.
*/
bool respuestaValida(const string &respuesta, const string& disponibles, const Dictionary &dic) {
    bool valida = true;
    string disponibles_copy = disponibles;
    //comprueba que las letras usadas están entre las disponibles
    for (char c : respuesta) {
        size_t pos = disponibles_copy.find(c);

        if (pos == string::npos) {
            valida = false;
            break;
        }

        //letra ya usada
        disponibles_copy.erase(pos,1);
    }

    //si las letras están bien usadas, comprueba si está en el diccionario
    if (valida){
        if (!dic.Esta(respuesta)) valida = false;
    }

    return valida;
}

int main(int argc, char *argv[]) {
    //PARÁMETROS
    if (argc != 5) {
        cout << "Uso: ./letras diccionario.txt letras.txt NUM MODO" << endl;
        cout << "MODO = L (longitud) | P (puntuación)" << endl;
        return 1;
    }

    string ficheroDic = argv[1];
    string ficheroLetras = argv[2];
    int num = stoi(argv[3]);
    char modo = argv[4][0];

    //CARGAR DICCIONARIO
    Dictionary dic;
    ifstream diccionario(ficheroDic);

    if(!diccionario) {
        cout << "Error al abrir el archivo diccionario: " << ficheroDic << endl;
        return 1;
    }

    diccionario >> dic;

    //CARGAR LETRAS
    LettersSet ls;
    ifstream dataLetras(ficheroLetras);

    if(!dataLetras) {
        cout << "Error al abrir el archivo letras: " << ficheroLetras << endl;
        return 1;
    }

    dataLetras >> ls;

    //CREAR BOLSA

    srand(time(NULL)); //inicializamos el generador de números aleatorios

    LettersBag bag(ls);

    //SACAMOS LETRAS
    char volver = 'S';

    while (volver == 'S'){
        string disponibles = bag.getMultiple(num);

        cout << "Letras generadas: " << endl;

        for (char c : disponibles) {
            cout << c << " ";
            if (modo == 'P') {
                cout << ls.getLetra(c).puntuacion << endl;
            }
        }

        //INTERACCIÓN CON USUARIO
        cout << endl << "Introduce tu respuesta: ";
        string respuesta;
        cin >> respuesta;
        minuscular(respuesta);

        //COMPROBACIÓN DE VALIDEZ
        bool valida = respuestaValida(respuesta, disponibles, dic);
        if (valida) {
            cout << "Su palabra es VÁLIDA ";
        }else {
            cout << "Su palabra NO ES VÁLIDA. " << endl;
        }

        //GENERACIÓN DE SOLUCIONES ÓPTIMAS
        vector<string> soluciones_optimas;

        int valor = 0;

        if (modo == 'L') {
            if (valida) cout << "y su longitud es " << respuesta.size() << "." << endl;
            soluciones_optimas = modoL(dic, disponibles, valor);
        } else if (modo == 'P') {
            if (valida) cout << "y supone " << ls.sumaPuntuaciones(respuesta) << " puntos." << endl;
            soluciones_optimas = modoP(dic, ls, disponibles, valor);
        } else {
            cout << "El modo debe ser 'L' o 'P'" << endl;
            return 1;
        }

        //SALIDA
        cout << endl << "SOLUCIONES ÓPTIMAS: " << endl;

        if (!soluciones_optimas.empty()) {
            if (modo == 'L')    cout << "LONGITUD: ";
            if (modo == 'P')    cout << "PUNTUACIÓN: ";
        }

        cout << valor << endl;

        for(const string& s : soluciones_optimas) {
            cout << "* " << s << endl;
        }

        //¿VOLVER A JUGAR?
        do {
            cout << endl << "¿Quieres seguir jugando[S/N]? ";
            cin >> volver;
        }while(volver != 'S' && volver != 'N');
    }


    return 0;
}
