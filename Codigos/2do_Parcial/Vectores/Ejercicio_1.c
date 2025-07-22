#include <stdio.h>
#define MAX 100

//R_1:El sistema debe solicitar al usuario el número de términos (n) a generar, con un máximo de MAX = 100.
//R_2:El sistema debe validar que n esté en el rango permitido (1 a 100). Si no, mostrará un mensaje de error y terminará.
//R_3:El sistema debe calcular cada término de la sucesión usando la fórmula y almacenarlo en un vector.
//R_4:El sistema debe imprimir los términos generados en formato lista.

int main() {
    int n;
    int vec[MAX];
    int k, VK;
    printf("Ingrese los terminos de la sucesion se desea generar? (1-%d): ", MAX);
    scanf("%d", &n);
    if (n > MAX || n <= 0) {
        printf("Error: Debes ingresar un numero entre 1 y %d\n", MAX);
        return 1;
    }
    for (int posicion = 0; posicion < n; posicion++) {
        k = posicion + 1;
        VK = k * k + 3;
        vec[posicion] = VK;
    }
    printf("\nLos primeros %d terminos de la sucesion son:\n", n);
    for (int posicion = 0; posicion < n; posicion++) {
        printf("Termino %d: %d\n", posicion + 1, vec[posicion]);
    }

    return 0;
}

//NRC: #20823_G8_FP
//Colaboradores
//Astudillo Adriana
//Muñoz Sarahi
//Nero Alan
