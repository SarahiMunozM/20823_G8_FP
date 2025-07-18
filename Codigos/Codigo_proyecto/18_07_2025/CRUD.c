#include <stdio.h>
#include <string.h>
#include <windows.h>

#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#define MAX_NOMBRE 50
#define MAX_PRODUCTOS 1000
#define ARCHIVO "inventario.txt"

typedef struct {
    char id[20];
    char Producto[50];
    char Marca[50];
    int Cantidad;
} Estudiante;

Estudiante lista[MAX_PRODUCTOS];
int cantidad = 0;

// RF2: Guardar en archivo
void guardarEnArchivo() {
    FILE *archivo = fopen(ARCHIVO, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) > 0) {
            fprintf(archivo, "%s|%s|%s|%d\n", lista[i].id, lista[i].Producto, lista[i].Marca, lista[i].Cantidad);
        }
    }

    fclose(archivo);
}

// RF2: Cargar desde archivo
void cargarDesdeArchivo() {
    FILE *archivo = fopen(ARCHIVO, "r");
    if (archivo == NULL) {
        return;
    }

    while (fscanf(archivo, "%[^|]|%[^|]|%[^|]|%d\n",
                  lista[cantidad].id,
                  lista[cantidad].Producto,
                  lista[cantidad].Marca,
                  &lista[cantidad].Cantidad) == 4) {
        cantidad++;
    }

    fclose(archivo);
}

// RF5: Buscar por nombre de producto
int buscarPorNombre(char nombre[]) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].Producto, nombre) == 0 && strlen(lista[i].id) > 0) {
            return i;
        }
    }
    return -1;
}

// RF1: Verifica que el ID sea único
int idUnico(char id[]) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].id, id) == 0 && strlen(lista[i].id) > 0) {
            return 0;
        }
    }
    return 1;
}

// RF1: Crear producto
void crearEstudiante(Estudiante *e) {
    while (1) {
        printf("Ingrese ID: ");
        fgets(e->id, 20, stdin);
        e->id[strcspn(e->id, "\n")] = '\0';

        if (idUnico(e->id)) {
            break;
        } else {
            printf("Error: El ID ya existe. Intente nuevamente.\n");
        }
    }

    printf("Ingrese Producto: ");
    fgets(e->Producto, 50, stdin);
    e->Producto[strcspn(e->Producto, "\n")] = '\0';

    printf("Ingrese Marca: ");
    fgets(e->Marca, 50, stdin);
    e->Marca[strcspn(e->Marca, "\n")] = '\0';

    printf("Ingrese Cantidad: ");
    scanf("%d", &e->Cantidad);
    getchar();

    printf(GREEN "Producto agregado exitosamente.\n" RESET); // Confirmación RF1
}

// RF1 y RF6: Mostrar producto con alerta de stock bajo
void mostrarEstudiante(Estudiante e) {
    printf("\nID: %s\n", e.id);
    printf("Producto: %s\n", e.Producto);
    printf("Marca: %s\n", e.Marca);
    printf("Cantidad: %d\n", e.Cantidad);

    // RF6: Alerta por bajo stock
    if (e.Cantidad <= 5) {
        printf("\x1b[31m¡ALERTA: Stock bajo!\x1b[0m\n");
    }
}

// RF5: Buscar por ID
int buscarPorID(Estudiante lista[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// RF3: Eliminar producto
void eliminarEstudiante(Estudiante *e) {
    strcpy(e->id, "");
    strcpy(e->Producto, "");
    strcpy(e->Marca, "");
    e->Cantidad = 0;
}

// RF4: Ordenar productos alfabéticamente por nombre
void ordenarPorNombre() {
    Estudiante temp;
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (strcmp(lista[i].Producto, lista[j].Producto) > 0) {
                temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
}

int main() {
    int opcion;
    char idBuscada[20];
    char nombreBuscado[50];

    cargarDesdeArchivo(); // RF2

    while (1) {
        printf(GREEN "\n=== SISTEMA DE INVENTARIO ===\n" RESET);
        printf("1. Agregar Productos\n");             // RF1
        printf("2. Mostrar Productos (Ordenados)\n"); // RF4 + RF6
        printf("3. Buscar por Nombre\n");            // RF5
        printf("4. Eliminar Producto\n");            // RF3
        printf("5. Salir\n");
        printf("Indique que desea realizar: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 1) {
            crearEstudiante(&lista[cantidad]);
            cantidad++;
            guardarEnArchivo();
        } else if (opcion == 2) {
            ordenarPorNombre(); // RF4
            for (int i = 0; i < cantidad; i++) {
                if (strlen(lista[i].id) > 0)
                    mostrarEstudiante(lista[i]); // RF6
            }
        } else if (opcion == 3) {
            printf("Ingrese el nombre del producto a buscar: ");
            fgets(nombreBuscado, 50, stdin);
            nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';

            int pos = buscarPorNombre(nombreBuscado);
            if (pos != -1) {
                mostrarEstudiante(lista[pos]);
            } else {
                printf("Producto no encontrado.\n");
            }
        } else if (opcion == 4) {
            printf("Ingrese el ID del producto a eliminar: ");
            fgets(idBuscada, 20, stdin);
            idBuscada[strcspn(idBuscada, "\n")] = '\0';

            int pos = buscarPorID(lista, cantidad, idBuscada);
            if (pos != -1 && strlen(lista[pos].id) > 0) {
                eliminarEstudiante(&lista[pos]);
                guardarEnArchivo();
                printf("Producto eliminado.\n");
            } else {
                printf("Producto no encontrado.\n");
            }
        } else if (opcion == 5) {
            printf("Saliendo...\n");
            break;
        } else {
            printf("Opción no válida. Intente nuevamente.\n");
        }
    }

    return 0;
}
