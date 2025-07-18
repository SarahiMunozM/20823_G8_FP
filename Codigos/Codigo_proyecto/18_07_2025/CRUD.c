#include <stdio.h>
#include <string.h>
#include <windows.h>

#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#define MAX_NOMBRE 50
#define MAX_PRODUCTOS 1000
#define ARCHIVO "inventario.txt"

// Definición de la estructura Productos
typedef struct {
    char id[20];       
    char Producto[50]; 
    char Marca[50];    
    int Cantidad;      
} Estudiante;

// Lista global de productos
Estudiante lista[MAX_PRODUCTOS];
int cantidad = 0;

// Función para guardar los datos en el archivo
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

// Función para cargar datos desde el archivo al iniciar
void cargarDesdeArchivo() {
    FILE *archivo = fopen(ARCHIVO, "r");
    if (archivo == NULL) {
        return; // No hay archivo todavía, se considera normal
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

// Función para agregar Productos
void crearEstudiante(Estudiante *e) {
    printf("Ingrese ID: ");
    fgets(e->id, 20, stdin);
    e->id[strcspn(e->id, "\n")] = '\0';

    printf("Ingrese Producto: ");
    fgets(e->Producto, 50, stdin);
    e->Producto[strcspn(e->Producto, "\n")] = '\0';

    printf("Ingrese Marca: ");
    fgets(e->Marca, 50, stdin);
    e->Marca[strcspn(e->Marca, "\n")] = '\0';

    printf("Ingrese Cantidad: ");
    scanf("%d", &e->Cantidad);
    getchar(); // Limpia el buffer del teclado
}

// Función para mostrar los datos de un Producto
void mostrarEstudiante(Estudiante e) {
    printf("\nID: %s\n", e.id);
    printf("Producto: %s\n", e.Producto);
    printf("Marca: %s\n", e.Marca);
    printf("Cantidad: %d\n", e.Cantidad);
}

// Función para buscar un Producto por ID
// Retorna la posición si lo encuentra, -1 si no existe
int buscarPorID(Estudiante lista[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// Función para eliminar un Producto (vacía el registro)
void eliminarEstudiante(Estudiante *e) {
    strcpy(e->id, "");
    strcpy(e->Producto, "");
    strcpy(e->Marca, "");
    e->Cantidad = 0;
}

int main() {
    int opcion;
    char idBuscada[20];

    // Carga productos existentes desde el archivo
    cargarDesdeArchivo();

    while (1) {
        printf(GREEN "\n=== SISTEMA DE INVENTARIO ===\n" RESET);
        printf("1. Agregar Productos\n");
        printf("2. Mostrar todos los Productos\n");
        printf("3. Buscar por ID\n");
        printf("4. Eliminar Productos\n");
        printf("5. Salir\n");
        printf("Indique que desea realizar: ");
        scanf("%d", &opcion);
        getchar(); // Limpia el buffer

        if (opcion == 1) {
            // Agrega un nuevo producto
            crearEstudiante(&lista[cantidad]);
            cantidad++;
            guardarEnArchivo();
        } else if (opcion == 2) {
            // Muestra todos los productos registrados
            for (int i = 0; i < cantidad; i++) {
                if (strlen(lista[i].id) > 0)
                    mostrarEstudiante(lista[i]);
            }
        } else if (opcion == 3) {
            // Busca un producto por ID
            printf("Ingrese el ID a buscar: ");
            fgets(idBuscada, 20, stdin);
            idBuscada[strcspn(idBuscada, "\n")] = '\0';

            int pos = buscarPorID(lista, cantidad, idBuscada);
            if (pos != -1 && strlen(lista[pos].id) > 0)
                mostrarEstudiante(lista[pos]);
            else
                printf("Producto no encontrado.\n");
        } else if (opcion == 4) {
            // Elimina un producto por ID
            printf("Ingrese el ID a eliminar: ");
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
            // Opción para salir del programa
            printf("Saliendo...\n");
            break;
        } else {
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    }

    return 0;
}
