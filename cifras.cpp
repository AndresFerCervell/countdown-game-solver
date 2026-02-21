/**
 * @file cifras.cpp
 * @brief Programa para resolver el juego de las Cifras.
 *
 * Utiliza un algoritmo recursivo para encontrar una combinación de operaciones
 * que llegue al número objetivo o, en su defecto, al más próximo.
 * Programa hecho por Miguel Crespo Orti y Andrés Fernández Cervell
 * Se ha usado IA para las siguientes funciones: SetAleatorio e intAleatorio.
 * Además, una vez resuelto, le pasamos el programa a la IA para comprobar errores y mejorar la
 * eficiencia.
 * Nos ayudó para optimizar la búsqueda de la mejor aproximación (queda comentado al final del
 * código nuestro primer boceto).
 */

#include <iostream>
#include <set>
#include <vector>
#include <cstdlib> // Necesario para rand() y srand()
#include <ctime>   // Necesario para time()
#include <algorithm> // Necesario para random_shuffle
#include <climits>
#include <random>
using namespace std;
/**
* @brief Struct global para almacenar la mejor aproximación.
*
* Se usa cuando no encontramos la solución exacta. Guarda el valor más cercano,
* la diferencia con el objetivo y la cadena de operaciones para llegar a él.
*/
struct MejorSolucion {
   int valor;      /**< El número más cercano conseguido */
   int dif;    /**< Diferencia con el objetivo (inicializada al máximo) */
   string cad;           /**< Pasos para conseguir el valor */
};

/**
 * @brief Convierte el contenido de un multiset a un string.
 *
 * Sirve para mostrar por pantalla los números disponibles separados por comas.
 *
 * @param S El multiset de números a imprimir.
 * @return Una cadena con los números formateados.
 */
string imprimirSet(const multiset<int> & S) {
    multiset<int>::iterator p = S.begin();
    string cad;
    while (p != S.end()) {
       if (p != --S.end())
          cad += to_string(*p) + ", ";
       else cad += to_string(*p);
       ++p;
    }
    return cad;
}

/**
 * @brief Selecciona n números aleatorios de un conjunto dado.
 *
 * Pasa los elementos a un vector para poder barajarlos y coge los n primeros.
 *
 * @param s El multiset original con todas las cifras posibles.
 * @param n Cantidad de números que queremos sacar.
 * @return Un nuevo multiset con los n elementos seleccionados.
 */

multiset<int> SetAleatorio(const multiset<int> & s, int n) {
   vector<int> listaTemporal(s.begin(), s.end()); // Forma más corta de copiar el set al vector

   // Configuración del generador aleatorio moderno
   random_device rd;
   mt19937 g(rd()); // Generador Mersenne Twister (mucho mejor que rand())

   // Barajar usando el generador
   shuffle(listaTemporal.begin(), listaTemporal.end(), g);

   multiset<int> resultado;
   if (n > listaTemporal.size()) n = listaTemporal.size();

   for(int i = 0; i < n; i++) {
      resultado.insert(listaTemporal[i]);
   }
   return resultado;
}

/**
 * @brief Genera el número objetivo aleatorio.
 *
 * @param n Máximo número de cifras que puede tener (potencia de 10).
 * @return Un entero aleatorio dentro del rango permitido.
 */
int intAleatorio(int n) {
    // Calculamos el límite (Ejemplo: si n=2, limite=100)
    int limite = 1;
    for(int i = 0; i < n; i++) {
       limite = limite * 10;
    }

   // Configuración del generador (se crea uno localmente)
   random_device rd;
   mt19937 gen(rd());

   // Distribución uniforme entre 0 y limite - 1
   // Es el equivalente moderno y preciso a: rand() % limite
   uniform_int_distribution<> dis(0, limite - 1);

   return dis(gen);
}


/**
 * @brief Realiza las 4 operaciones básicas entre dos números del set.
 *
 * Crea nuevos sets sustituyendo los dos números elegidos por el resultado de
 * operarlos (suma, resta, multiplicación y división).
 *
 * @param S El set actual de números.
 * @param p Iterador al primer operando.
 * @param q Iterador al segundo operando.
 * @return Un vector con 4 multisets (uno por cada operación posible).
 * Si una operación no es válida, devuelve un set con un -1.
 */
vector<multiset<int> > OperaSet(const multiset<int> & S, const multiset<int>::iterator & p, const multiset<int>::iterator & q) {
    multiset<int> Saux(S);
    int el1 = *p;
    int el2 = *q;
    //Para borrar solo una aparición del elemento
    multiset<int>::iterator it1 = Saux.find(el1);
    Saux.erase(it1);
    multiset<int>::iterator it2 = Saux.find(el2);
    Saux.erase(it2);

    vector<multiset<int> > v(4);
    v[0] = Saux;                 //Se guarda la suma
    v[0].insert(el1 + el2);
    if (el1 - el2 >= 0){         //La resta no debe tener resultado negativo
    v[1] = Saux;                 //Se guarda la resta
    v[1].insert(el1 - el2);
    } else
       v[1] = {-1};              //Si la resta es inválida, se  guarda un -1
    v[2] = Saux;                 //Se guarda la multiplicación
    v[2].insert(el1 * el2);
    if (el2 != 0 && el1 % el2 == 0) {  //La división debe ser entera
       v[3] = Saux;
       v[3].insert(el1 / el2);       //Se guarda la división
    }
    else
       v[3] = {-1};                 //Si la división no es entera, se guarda un -1
    return v;
}

/**
 * @brief Función recursiva para resolver el problema.
 *
 * Busca si se puede alcanzar M operando los números de S. Si no encuentra
 * el exacto, va guardando la mejor aproximación en la variable global.
 *
 * @param S Conjunto de números disponibles en este paso.
 * @param M El número objetivo a conseguir.
 * @param cad String pasado por referencia donde se construye la solución.
 * @return true si encuentra la solución exacta, false en caso contrario.
 */
bool problema_cifras(const multiset<int> & S, int M, string &cad, struct MejorSolucion & mejorsolucion){


    multiset<int>::iterator p = S.begin();
    while (p != S.end()) {
       multiset<int>::iterator q = S.begin();
       if (S.find(M) != S.end())  //El elemento está en el conjunto => terminamos
          return true;
       //Buscamos la mejor aproximación:
       multiset<int>::iterator it = S.begin();
       while (it != S.end()) {
          if (abs(M - *it) < mejorsolucion.dif) {
             mejorsolucion.valor = *it;
             mejorsolucion.dif = abs(M - *it);
          }
          ++it;
       }


       if (S.size() == 0 || S.size() == 1)    //El set es vacío o tiene un único elemento y es distinto de M
          return false;
       while (q != S.end() && q != p) {
          vector<multiset<int>> v = OperaSet(S, p , q);
          if (problema_cifras(v[0], M, cad, mejorsolucion)) {      //Suma
             cad = "\n" + to_string(*p) + "+" + to_string(*q) + "=" + to_string(*p+*q) + cad;
             return true;
          }
          if (!v[1].empty() && *v[1].begin() != -1) { //Si v[1] = {-1} no se hace nada
             if (problema_cifras(v[1], M, cad, mejorsolucion)) { //Resta.
                cad = "\n" + to_string(*p) + "-" + to_string(*q) + "=" + to_string(*p-*q) + cad;
                return true;
             }
          }
          if (problema_cifras(v[2], M, cad, mejorsolucion)) {   //Multiplicación
             cad = "\n" + to_string(*p) + "*" + to_string(*q) + "=" + to_string(*p**q) + cad;
             return true;
          }
          if (!v[3].empty() && *v[3].begin() != -1) {       //Si v[1] = {-1} no se hace nada
             if (problema_cifras(v[3], M, cad, mejorsolucion)) { //División.
                cad = "\n" + to_string(*p) + "/" + to_string(*q) +"=" + to_string(*p/ *q) + cad;
                return true;
             }
          }

       ++q;
       }
       ++p;
    }
    return false;

}

int main() {
    const multiset <int> C = {1,2,3,4,5,6,7,8,9, 10, 25, 50, 75, 100}; //Conjunto del que obtenemos un set aleatorio
    const int NUMALEATORIOS = 6;   //Número de elementos que va a tener nuestro set aleatorio
    const int NUMCIFRAS = 3;      //Número de cifras del elemento a buscar
    string   cad;              //Cadena para guardar las operaciones
    //Inicialización de mejorsolucion:
    MejorSolucion mejorsolucion;
    mejorsolucion.dif = INT_MAX;
    mejorsolucion.valor = -1;


    multiset<int> s = SetAleatorio(C,NUMALEATORIOS);
    int M = intAleatorio(NUMCIFRAS);
    cout << "Dados los números: " << imprimirSet(s) << endl << "Buscamos el número: " << M << endl;
    bool    result = problema_cifras(s, M, cad,mejorsolucion);
    if (result) {
       cout << "Existe solución: " <<  cad << endl;
    }
    else {
       cout << "No existe solución. Buscamos la más próxima:  " << endl;

       problema_cifras(s, mejorsolucion.valor, mejorsolucion.cad, mejorsolucion);
       cout << "Existe solución en M = " << to_string(mejorsolucion.valor) << " con diferencia = "
          << to_string(mejorsolucion.dif) << endl<< "La solución es: " << mejorsolucion.cad << endl;

    }
    return 0;
}

/* //Idea descartada para buscar la solución más próxima por ser demasiado ineficiente.
       int i = 1;
       while (!result && i < M) {    //Si no había sol buscamos la más cercana sumando y restando 1 al número original
          result = problema_cifras(s, M - i, cad);
          if (result)
             cout << "Existe solución en M = " << to_string(M - i) << endl<< "La solución es: " << cad << endl;
          else {
             result = problema_cifras(s, M + i, cad);
             if (result)
                cout << "Existe solución en M = " << to_string(M + i) << endl<< "La solución es: " << cad << endl;

          }
          i++;
       }
       */
