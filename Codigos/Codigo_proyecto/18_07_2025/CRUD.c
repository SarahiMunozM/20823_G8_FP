#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

#define MAX_NOMBRE 50
#define MAX_PRODUCTOS 1000
#define ARCHIVO "inventario.txt"
#define ARCHIVO_VENTAS "ventas.txt"

// Datos del Produto
typedef struct {
    char id[20];
    char Producto[50];
    char Marca[50];
    int Cantidad;
} Estudiante;

// Estructura para el registro de ventas
typedef struct {
    char id[20];
    char Producto[50];
    int CantidadVendida;
    char fecha[30];
} Venta;

Estudiante lista[MAX_PRODUCTOS];
int cantidad = 0;

// RF2: Guardar productos en archivo
void guardarEnArchivo() {
    FILE *archivo = fopen(ARCHIVO, "w");
    if (archivo == NULL) {
        printf("Error al abrir archivo.\n");
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) > 0) {
            fprintf(archivo, "%s|%s|%s|%d\n", lista[i].id, lista[i].Producto, lista[i].Marca, lista[i].Cantidad);
        }
    }
    fclose(archivo);
}

// RF2: Cargar productos desde archivo
void cargarDesdeArchivo() {
    FILE *archivo = fopen(ARCHIVO, "r");
    if (archivo == NULL) return;

    while (fscanf(archivo, "%[^|]|%[^|]|%[^|]|%d\n",
                  lista[cantidad].id,
                  lista[cantidad].Producto,
                  lista[cantidad].Marca,
                  &lista[cantidad].Cantidad) == 4) {
        cantidad++;
    }
    fclose(archivo);
}

// RF5: Búsqueda por ID
int buscarPorID(Estudiante lista[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// RF5: Búsqueda por nombre
int buscarPorNombre(char nombre[]) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].Producto, nombre) == 0 && strlen(lista[i].id) > 0) {
            return i;
        }
    }
    return -1;
}

// RF1: Validación de ID único
int idUnico(char id[]) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].id, id) == 0 && strlen(lista[i].id) > 0) {
            return 0;
        }
    }
    return 1;
}

// RF1: Crear producto con validación y confirmación
void crearEstudiante(Estudiante *e) {
    while (1) {
        printf("Ingrese ID: ");
        fgets(e->id, 20, stdin);
        e->id[strcspn(e->id, "\n")] = '\0';

        if (idUnico(e->id)) break;
        else printf("Error: ID ya existe. Intente nuevamente.\n");
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

    printf(GREEN "Producto agregado exitosamente.\n" RESET);
}

// RF6: Mostrar producto con alerta de bajo stock
void mostrarEstudiante(Estudiante e) {
    printf("\nID: %s\n", e.id);
    printf("Producto: %s\n", e.Producto);
    printf("Marca: %s\n", e.Marca);
    printf("Cantidad: %d\n", e.Cantidad);

    if (e.Cantidad <= 5) {
        printf("\x1b[31mALERTA: Stock bajo!\x1b[0m\n");
    }
}

// RF3: Eliminar producto
void eliminarEstudiante(Estudiante *e) {
    strcpy(e->id, "");
    strcpy(e->Producto, "");
    strcpy(e->Marca, "");
    e->Cantidad = 0;
}

// RF4: Ordenar productos por nombre (orden alfabético)
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

// RF7: Registrar venta
void registrarVenta() {
    char id[20];
    int cantidadVendida;

    printf("Ingrese ID del producto a vender: ");
    fgets(id, 20, stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = buscarPorID(lista, cantidad, id);
    if (pos == -1 || strlen(lista[pos].id) == 0) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Ingrese cantidad a vender: ");
    scanf("%d", &cantidadVendida);
    getchar();

    if (cantidadVendida <= 0 || cantidadVendida > lista[pos].Cantidad) {
        printf("Cantidad no válida o insuficiente en stock.\n");
        return;
    }

    lista[pos].Cantidad -= cantidadVendida;
    guardarEnArchivo();

    // Obtener fecha actual
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char fecha[30];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", tm_info);

    // RF7: Guardar venta en archivo
    FILE *ventas = fopen(ARCHIVO_VENTAS, "a");
    if (ventas != NULL) {
        fprintf(ventas, "%s|%s|%d|%s\n",
                lista[pos].id,
                lista[pos].Producto,
                cantidadVendida,
                fecha);
        fclose(ventas);
    }

    printf(GREEN "Venta registrada exitosamente.\n" RESET);
}

// RF8: Mostrar ventas del día
void mostrarVentasDelDia() {
    FILE *ventas = fopen(ARCHIVO_VENTAS, "r");
    if (ventas == NULL) {
        printf("No hay registro de ventas.\n");
        return;
    }

    char fechaActual[11];
    time_t t = time(NULL);
    strftime(fechaActual, sizeof(fechaActual), "%Y-%m-%d", localtime(&t));

    printf(GREEN "\nVentas realizadas hoy (%s):\n" RESET, fechaActual);
    printf("-----------------------------------\n");

    char linea[200];
    int totalVendidos = 0;

    while (fgets(linea, sizeof(linea), ventas)) {
        Venta v;
        sscanf(linea, "%[^|]|%[^|]|%d|%[^\n]", v.id, v.Producto, &v.CantidadVendida, v.fecha);

        if (strncmp(v.fecha, fechaActual, 10) == 0) {
            printf("Producto: %s | Cantidad: %d | Fecha: %s\n", v.Producto, v.CantidadVendida, v.fecha);
            totalVendidos += v.CantidadVendida;
        }
    }

    printf("-----------------------------------\n");
    printf("Total productos vendidos hoy: %d\n", totalVendidos);

    fclose(ventas);
}

// Menú principal
int main() {
    int opcion;
    char nombreBuscado[50];

    cargarDesdeArchivo(); // RF2

    while (1) {
        printf(GREEN "\n=== SISTEMA DE INVENTARIO ===\n" RESET);
        printf("1. Agregar Productos\n");             // RF1
        printf("2. Mostrar Productos (Ordenados)\n"); // RF4 + RF6
        printf("3. Buscar por Nombre\n");            // RF5
        printf("4. Eliminar Producto\n");            // RF3
        printf("5. Registrar Venta\n");              // RF7
        printf("6. Ver Ventas del Dia\n");           // RF8
        printf("7. Salir\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        if (opcion == 1) {
            crearEstudiante(&lista[cantidad]);
            cantidad++;
            guardarEnArchivo();
        } else if (opcion == 2) {
            ordenarPorNombre(); // RF4
            for (int i = 0; i < cantidad; i++) {
                if (strlen(lista[i].id) > 0) {
mostrarEstudiante(lista[i]);
}
}
} else if (opcion == 3) {
printf("Ingrese el nombre del producto: ");
fgets(nombreBuscado, 50, stdin);
nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';
        int pos = buscarPorNombre(nombreBuscado);
        if (pos != -1) mostrarEstudiante(lista[pos]);
        else printf("Producto no encontrado.\n");
    } else if (opcion == 4) {
        char idBuscado[20];
        printf("Ingrese el ID del producto a eliminar: ");
        fgets(idBuscado, 20, stdin);
        idBuscado[strcspn(idBuscado, "\n")] = '\0';

        int pos = buscarPorID(lista, cantidad, idBuscado);
        if (pos != -1 && strlen(lista[pos].id) > 0) {
            eliminarEstudiante(&lista[pos]);
            guardarEnArchivo();
            printf(GREEN "Producto eliminado.\n" RESET);
        } else {
            printf("Producto no encontrado.\n");
        }
    } else if (opcion == 5) {
        registrarVenta(); // RF7
    } else if (opcion == 6) {
        mostrarVentasDelDia(); // RF8
    } else if (opcion == 7) {
        printf("Saliendo...\n");
        break;
    } else {
        printf("Opción no válida.\n");
    }
}

return 0;
}
