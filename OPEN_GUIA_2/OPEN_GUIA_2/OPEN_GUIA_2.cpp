// GUIA_PARALEL_COMPUTING.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Librerias

#include <iostream>  // Librería estándar para entrada/salida
#include <omp.h>     // Librería para programación paralela con OpenMP

// Variables

#define N 1000        // Tamaño del arreglo (Elementos a manejar en el arreglo) 
#define chunk 100     // Tamaño de los pedazos para el scheduling (El tamaño de valores de los arreglos)
#define mostrar 10    // Número de elementos a mostrar

// Funciones

void imprimeArreglo(float* d);

// Funcion Main

int main()
{
    // Asignacion de arreglos
    std::cout << "Sumando Arreglos en Paralelo!\n";

    float a[N], b[N], c[N]; // Arreglos
    int i;   // Índice para recorrer los arreglos

    // Iniciando los arreglos a y b dandoles valores
    for (i = 0; i < N; i++) {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    int pedazos = chunk;

    // Establecer el número de hilos
    omp_set_num_threads(4); // Cambia este valor según el número de hilos que desees utilizar

    // Verifico el número de hilos disponibles
    int num_threads = omp_get_max_threads();
    std::cout << "Numero maximo de hilos disponibles: " << num_threads << std::endl;

    // Medir el tiempo de ejecución
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

    // Verificar el número de hilos activos dentro de la región paralela
#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        if (thread_num == 0) {
            std::cout << "Numero de hilos activos en la region paralela: " << num_threads << std::endl;
        }
    }

    // Medir el tiempo de ejecución
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    // Seccion para imprimir los ciclos y sus resultados

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    std::cout << "Tiempo de ejecución: " << execution_time << " segundos" << std::endl;

    std::cout << "Fin De Codigo!\n";
}

// Función para imprimir un arreglo
// Definición de la función fuera de `main()`
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}