#include <stdio.h>
#include <limits.h> 

// Para INT_MAX
//El sistema debe almacenar números enteros del 1 al 15 en un arreglo (Vec).
//El sistema debe calcular el factorial de cada número en Vec y almacenarlo en otro arreglo (Fact).
//El sistema debe imprimir una tabla con dos columnas: Número y Factorial, formateada para alinear los valores.
//El sistema debe usar el tipo unsigned long long para evitar desbordamiento en factoriales grandes.

int main() {
 const int n = 15;
 int Vec[n];

unsigned long long Fact[n];
 for(int i = 0; i < n; i++) {
 Vec[i] = i + 1;
 }
 for(int i = 0; i < n; i++) {
 Fact[i] = 1;
 for(int j = 1; j <= Vec[i]; j++) {
 Fact[i] *= j;
 }
 }
 printf("Numero | Factorial\n");
 printf("------------------\n");
 for(int i = 0; i < n; i++) {
 printf("%6d | %20llu\n", Vec[i], Fact[i]);
 }
 return 0;
}
//NRC: #20823_G8_FP
//Colaboradores
//Astudillo Adriana
//Muñoz Sarahi
//Nero Alan
