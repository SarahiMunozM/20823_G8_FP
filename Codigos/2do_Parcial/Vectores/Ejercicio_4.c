#include <stdio.h>
int main() {
//El sistema debe permitir al usuario ingresar 10 valores enteros y almacenarlos en un vector.
//El sistema debe ordenar los números en orden descendente (de mayor a menor).
//El sistema debe imprimir el vector ordenado en formato lista.
//El algoritmo de ordenamiento debe ser eficiente para entradas pequeñas
    int i;
    int j;
    int temp;
    int vector[10];

    
    /* Leer los valores del vector */
    for (i = 0; i < 10; i++) {
        printf("Ingrese el valor %d: \n", i + 1);
        scanf("%d", &vector[i]);
    }

    
    /* Ordenar el vector */
    for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 10; j++) {
            if (vector[i] < vector[j]) {
                temp = vector[i];
                vector[i] = vector[j];
                vector[j] = temp;
            }
        }
    }
    /* Imprimir el vector ordenado */
    printf("Vector ordenado: \n");
    for (i = 0; i < 10; i++) {
        printf("%d\n", vector[i]);
    }
    return 0;
}
//NRC: #20823_G8_FP
//Colaboradores
//Astudillo Adriana
//Muñoz Sarahi
//Nero Alan
