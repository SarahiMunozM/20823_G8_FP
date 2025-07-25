#include <stdio.h>
#include <string.h>

// Definición del TDA Estudiante
typedef struct {
    int id;
    char nombre[50];
    char asignatura[50];
    float nota_p_1;
    float nota_p_2;
    float nota_p_3;
    float promedio;
    char estado[10];
} Estudiante;

// Función para mostrar un estudiante
void mostrarEstudiante(Estudiante e) {
    printf("ID: %d\n", e.id);
    printf("Nombre: %s\n", e.nombre);
    printf("Asignatura: %s\n", e.asignatura);
    printf("Nota Primer Parcial: %.2f\n", e.nota_p_1);
    printf("Nota Segundo Parcial: %.2f\n", e.nota_p_2);
    printf("Nota Tercer Parcial: %.2f\n", e.nota_p_3);
    printf("Promedio: %.2f\n", e.promedio);
    printf("Estado: %s\n", e.estado);
}

// Función para calcular el promedio
float calcularPromedio(float nota1, float nota2, float nota3) {
    return (nota1 + nota2 + nota3) / 3;
}
void verificarAprobacion(Estudiante* e) {
    if (e->promedio >= 14.0) {
        strcpy(e->estado, "Aprobado");
    } else {
        strcpy(e->estado, "Reprobado");
    }
}

int main() {
    // Declaración e inicialización de un estudiante con notas
    Estudiante estudiante1 = {1, "Genesis Vivas","Calculo Diferencial e Integral", 14.0, 4.5, 1.0, 0, ""};

    // Calcular el promedio del estudiante 1
    estudiante1.promedio = calcularPromedio(estudiante1.nota_p_1, estudiante1.nota_p_2, estudiante1.nota_p_3);
    verificarAprobacion(&estudiante1);

    printf("Ejemplo 1 - Estudiante Individual\n");
    mostrarEstudiante(estudiante1);

    // Almacenamiento en arreglo de estructuras
    Estudiante lista[3];

    // Inicialización de los estudiantes en la lista
    lista[0].id = 2;
    strcpy(lista[0].nombre, "Damaris Valdiviezo");
    strcpy(lista[0].asignatura, "Algebra Lineal");
    lista[0].nota_p_1 = 15.0;
    lista[0].nota_p_2 = 9.5;
    lista[0].nota_p_3 = 8.2;
    lista[0].promedio = calcularPromedio(lista[0].nota_p_1, lista[0].nota_p_2, lista[0].nota_p_3);
    verificarAprobacion(&lista[0]);

    lista[1].id = 3;
    strcpy(lista[1].nombre, "Ronald Garcia");
    strcpy(lista[1].asignatura, "Fundamentos de Programacion");
    lista[1].nota_p_1 = 14.8;
    lista[1].nota_p_2 = 17.9;
    lista[1].nota_p_3 = 18.2;
    lista[1].promedio = calcularPromedio(lista[1].nota_p_1, lista[1].nota_p_2, lista[1].nota_p_3);
    verificarAprobacion(&lista[1]);

    lista[2].id = 4;
    strcpy(lista[2].nombre, "Alisson Morales");
    strcpy(lista[2].asignatura, "Quimica");
    lista[2].nota_p_1 = 20.0;
    lista[2].nota_p_2 = 10.1;
    lista[2].nota_p_3 = 17.0;
    lista[2].promedio = calcularPromedio(lista[2].nota_p_1, lista[2].nota_p_2, lista[2].nota_p_3);
    verificarAprobacion(&lista[2]);

    // Mostrar lista de estudiantes
    printf("\nEjemplo 2 - Lista de Estudiantes\n");
    for (int i = 0; i < 3; i++) {
        mostrarEstudiante(lista[i]);
        printf("----------------------\n");
    }

    return 0;
}
