# Countdown Game Engine (C++ Solver)

An efficient, high-performance C++ implementation of the solvers for the popular "Countdown" game (Cifras y Letras).

## Overview

This repository provides two specialized solvers:

1. **Numbers Round (Cifras):** A mathematical engine that finds the exact sequence of operations to reach a target number (randomly generated) or the closest possible approximation. It features a complex recursive backtracking engine, using STL containers such as `std::set` and `std::multiset`.
 
2. **Letters Round (Letras):** A linguistic engine that identifies the longest possible words from a given set of letters by utilizing an optimized lexicon search. A bag of as many letters as the user types is randomly generated, and he may play introducing the highest-scoring word formed by those letters. The program validates that word, and shows the most optimal solutions. The type of punctuation can be selected by the user when running the programme. It can be either for length of the words, or an algorithm that awards using the least common letters.

## Technical Features

### Numbers Solver (Arithmetic Backtracking)
The numbers engine explores the state space of basic arithmetic operations (`+`, `-`, `*`, `/`) using a **Recursive Backtracking** approach.
* **Exhaustive Search:** Explores all valid combinations of the source numbers.
* **Heuristic Approximation:** If an exact solution is not found, the algorithm tracks and returns the closest result found during execution.

### Letters Solver (Lexicon Search)
The letters engine is built with a **modular architecture** (14 files), demonstrating advanced C++ practices such as:
* **Modular Programming:** Clear separation between interfaces (`.h`) and implementations (`.cpp`).
* **Efficient Data Structures:** Utilization of STL containers (`std::set`, `std::vector`, `std::multiset`) to manage dictionary lookups and letter frequencies.

Furthermore, it is all documented in Spanish using Doxygen, and it includes a `Doxyfile` that explains the algorithms and data structures used.

## Requirements & Installation

* **Compiler:** C++11 or higher (GCC/Clang recommended).
* **Build System:** CMake (compatible with Linux/WSL).

### 1. Running the Numbers Game (Cifras)
Since the numbers solver is contained within a single file, you can compile it directly using `g++`:

Compile and run

```bash
g++ -std=c++11 cifras.cpp -o cifras_solver
./cifras_solver
```

### 2. Running the Letters Game (Letras)
The letters solver uses a standard out-of-source CMake build process and includes three distinct programs. From the root of the letras directory:


Create a build directory and compile

```bash
mkdir build && cd build
cmake ..
make
```
Once compiled, the executables will be located in the bin/ directory. You can run them from the root of the letras folder as follows:

#### A. The Main Game (letras) Plays the Countdown letters game. Requires the dictionary file, the letters file, the number of random letters to generate, and the game mode (L for longest word, P for highest score).

Example:
```bash
./bin/letras ./data/diccionario.txt ./data/letras.txt 8 L
```
#### B. Dictionary Test (testdiccionario) Loads the dictionary into memory and allows querying words of a specific length or checking word existence.

Example:
```bash
./bin/testdiccionario ./data/diccionario.txt
```

#### C. Letter Frequency Calculator (cantidad_letras) 
Reads the dictionary, calculates the frequency of each letter, and assigns a rarity score (1-10), outputting the result to a new file.

Example:
```bash
./bin/cantidad_letras ./data/diccionario.txt ./data/letras.txt salida.txt
```

## Academic Context & AI Disclosure
This project was developed during the 2nd year of the Double Degree in Computer Engineering & Mathematics at the University of Granada (UGR).

## Transparency note:
In alignment with open-source best practices and academic integrity guidelines, AI assistance was used strictly for generating specific randomizer helper functions (SetAleatorio and intAleatorio) and for reviewing the final code to optimize the closest-approximation heuristic. The core backtracking logic and data structure designs are original work.

## Authors
Andrés Fernández Cervell and Miguel Crespo Orti (miguelcrespoo)

## License
This project is licensed under the MIT License.
