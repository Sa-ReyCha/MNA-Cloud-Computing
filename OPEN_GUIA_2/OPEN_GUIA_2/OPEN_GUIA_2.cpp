// GUIA_PARALEL_COMPUTING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Librerias

#include <iostream>  // Librer�a est�ndar para entrada/salida
#include <omp.h>     // Librer�a para programaci�n paralela con OpenMP

// Variables

#define N 1000        // Tama�o del arreglo (Elementos a manejar en el arreglo) 
#define chunk 100     // Tama�o de los pedazos para el scheduling (El tama�o de valores de los arreglos)
#define mostrar 10    // N�mero de elementos a mostrar

// Funciones

void imprimeArreglo(float* d);

// Funcion Main

int main()
{
    // Asignacion de arreglos
    std::cout << "Sumando Arreglos en Paralelo!\n";

    float a[N], b[N], c[N]; // Arreglos
    int i;   // �ndice para recorrer los arreglos

    // Iniciando los arreglos a y b dandoles valores
    for (i = 0; i < N; i++) {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    int pedazos = chunk;

    // Establecer el n�mero de hilos
    omp_set_num_threads(4); // Cambia este valor seg�n el n�mero de hilos que desees utilizar

    // Verifico el n�mero de hilos disponibles
    int num_threads = omp_get_max_threads();
    std::cout << "Numero maximo de hilos disponibles: " << num_threads << std::endl;

    // Medir el tiempo de ejecuci�n
    double start_time = omp_get_wtime();

    // Suma de arreglos en paralelo con OpenMP
#pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i]; // Esto suma las listas en base indice i
        int thread_num = omp_get_thread_num();
        // Imprime que thread es el que paso y proceso
        // std::cout << "Thread " << thread_num << " processed index " << i << std::endl;
    }

    // Verificar el n�mero de hilos activos dentro de la regi�n paralela
#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        if (thread_num == 0) {
            std::cout << "Numero de hilos activos en la region paralela: " << num_threads << std::endl;
        }
    }

    // Medir el tiempo de ejecuci�n
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    // Seccion para imprimir los ciclos y sus resultados

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    std::cout << "Tiempo de ejecuci�n: " << execution_time << " segundos" << std::endl;

    std::cout << "Fin De Codigo!\n";
}

// Funci�n para imprimir un arreglo
// Definici�n de la funci�n fuera de `main()`
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}