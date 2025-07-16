#include <stdio.h>      // Librería estándar de entrada y salida
#include <string.h>     // Librería para manejo de cadenas
#include <windows.h>    // Librería específica para Windows (colores en consola)

#define GREEN "\x1b[32m" // Color verde para el texto
#define RESET "\x1b[0m"  // Resetea el color de texto

#define MAX_NOMBRE 50
#define MAX_PRODUCTOS 1000    // Máximo de productos que se pueden almacenar
#define ARCHIVO "inventario.txt" // Nombre del archivo donde se guarda el inventario

// Definición de la estructura para representar un producto
typedef struct {
    char id[20];         // ID del producto
    char Producto[50];   // Nombre del producto
    char Marca[50];      // Marca del producto
    int Cantidad;        // Cantidad disponible del producto
} Estudiante;

// Arreglo global donde se almacenan los productos
Estudiante lista[MAX_PRODUCTOS];
int cantidad = 0; // Número actual de productos registrados

// Función que guarda todos los productos actuales en el archivo
void guardarEnArchivo() {
    FILE *archivo = fopen(ARCHIVO, "w"); // Abre archivo en modo escritura (sobrescribe)
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    // Recorre todos los productos y los guarda en formato: id|Producto|Marca|Cantidad
    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) > 0) { // Solo guarda los registros no vacíos
            fprintf(archivo, "%s|%s|%s|%d\n",
                    lista[i].id,
                    lista[i].Producto,
                    lista[i].Marca,
                    lista[i].Cantidad);
        }
    }
    fclose(archivo); // Cierra el archivo
}

// Función que carga los productos desde el archivo al iniciar el programa
void cargarDesdeArchivo() {
    FILE *archivo = fopen(ARCHIVO, "r"); // Abre archivo en modo lectura
    if (archivo == NULL) {
        return; // Si el archivo no existe aún, simplemente se retorna
    }
    // Lee línea por línea cada producto separado por '|'
    while (fscanf(archivo, "%[^|]|%[^|]|%[^|]|%d\n",
                  lista[cantidad].id,
                  lista[cantidad].Producto,
                  lista[cantidad].Marca,
                  &lista[cantidad].Cantidad) == 4) {
        cantidad++; // Aumenta la cantidad de productos cada vez que se lee uno válido
    }
    fclose(archivo); // Cierra el archivo
}
// Función para ingresar un nuevo producto manualmente
void crearEstudiante(Estudiante *e) {
    printf("Ingrese ID: ");
    fgets(e->id, 20, stdin); // Lee el ID del producto
    e->id[strcspn(e->id, "\n")] = '\0'; // Elimina salto de línea

    printf("Ingrese Producto: ");
    fgets(e->Producto, 50, stdin); // Lee el nombre del producto
    e->Producto[strcspn(e->Producto, "\n")] = '\0'; // Elimina salto de línea

    printf("Ingrese Marca: ");
    fgets(e->Marca, 50, stdin); // Lee la marca del producto
    e->Marca[strcspn(e->Marca, "\n")] = '\0'; // Elimina salto de línea

    printf("Ingrese Cantidad: ");
    scanf("%d", &e->Cantidad); // Lee la cantidad disponible
    getchar(); // Limpia el buffer del teclado
}
// Función para mostrar en pantalla un producto
void mostrarEstudiante(Estudiante e) {
    printf("\nID: %s\n", e.id);
    printf("Producto: %s\n", e.Producto);
    printf("Marca: %s\n", e.Marca);
    printf("Cantidad: %d\n", e.Cantidad);
}
// Función para buscar un producto por su ID
// Devuelve la posición en el arreglo si lo encuentra, -1 si no existe
int buscarPorID(Estudiante lista[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id, id) == 0) {
            return i; // ID encontrado
        }
    }
    return -1; // No se encontró el ID
}
// Función para eliminar un producto (vaciando sus campos)
void eliminarEstudiante(Estudiante *e) {
    strcpy(e->id, "");
    strcpy(e->Producto, "");
    strcpy(e->Marca, "");
    e->Cantidad = 0;
}
// Función principal del programa
int main() {
    int opcion;           // Opción seleccionada en el menú
    char idBuscada[20];   // Buffer para buscar productos por ID

    cargarDesdeArchivo(); // Carga productos desde el archivo al iniciar

    while (1) {
        // Menú principal
        printf(GREEN "\n=== SISTEMA DE INVENTARIO ===\n" RESET);
        printf("1. Agregar Productos\n");
        printf("2. Mostrar todos los Productos\n");
        printf("3. Buscar por ID\n");
        printf("4. Eliminar Productos\n");
        printf("5. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion); // Lee la opción del usuario
        getchar(); // Limpia el buffer

        if (opcion == 1) {
            // Agrega un nuevo producto
            crearEstudiante(&lista[cantidad]); // Llama a la función de ingreso
            cantidad++; // Aumenta el contador total
            guardarEnArchivo(); // Guarda los cambios en el archivo
        } else if (opcion == 2) {
            // Muestra todos los productos disponibles
            for (int i = 0; i < cantidad; i++) {
                if (strlen(lista[i].id) > 0) // Solo muestra si el producto no está vacío
                    mostrarEstudiante(lista[i]);
            }
        } else if (opcion == 3) {
            // Buscar producto por ID
            printf("Ingrese el ID a buscar: ");
            fgets(idBuscada, 20, stdin);
            idBuscada[strcspn(idBuscada, "\n")] = '\0'; // Elimina salto de línea

            int pos = buscarPorID(lista, cantidad, idBuscada); // Busca el producto
            if (pos != -1 && strlen(lista[pos].id) > 0)
                mostrarEstudiante(lista[pos]); // Muestra si se encuentra
            else
                printf("Producto no encontrado.\n"); // Mensaje si no se encuentra
        } else if (opcion == 4) {
            // Eliminar producto por ID
            printf("Ingrese el ID a eliminar: ");
            fgets(idBuscada, 20, stdin);
            idBuscada[strcspn(idBuscada, "\n")] = '\0';

            int pos = buscarPorID(lista, cantidad, idBuscada);
            if (pos != -1 && strlen(lista[pos].id) > 0) {
                eliminarEstudiante(&lista[pos]); // Vacía el producto
                guardarEnArchivo(); // Guarda los cambios
                printf("Producto eliminado.\n");
            } else {
                printf("Producto no encontrado.\n");
            }
        } else if (opcion == 5) {
            // Opción para salir del programa
            printf("Saliendo...\n");
            break;
        } else {
            // Opción no válida
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    }

    return 0; // Fin del programa
}
