#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

//Colores para la consola
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

#define MAX_NOMBRE 50
#define MAX_PRODUCTOS 1000
#define CARPETA_INVENTARIO "inventario/"
#define ARCHIVO CARPETA_INVENTARIO "datos_inventario.txt"
#define ARCHIVO_VENTAS CARPETA_INVENTARIO "registro_ventas.txt"
#define ARCHIVO_BACKUP CARPERA_INVENTARIO "backup_inventario.txt"

//Estructura para almacenar información de productos
typedef struct {
    char id[20];
    char Producto[50];
    char Marca[50];
    int Cantidad;
} Producto;

//Estructura para el registro de ventas
typedef struct {
    char id[20];
    char Producto[50];
    int CantidadVendida;
    char fecha[30];
} Venta;

// Variables globales
Producto lista[MAX_PRODUCTOS];
int cantidad = 0;

//RF2: Guardar productos en archivo y Cargar productos desde archivo
void crearCarpetaInventario() {
    #ifdef _WIN32
        system("mkdir inventario 2> nul");
    #else
        system("mkdir -p inventario");
    #endif
}
void guardarEnArchivo() {
    FILE *archivo = fopen(ARCHIVO, "w");
    if (archivo == NULL) {
        printf(RED "Error: No se pudo abrir %s\n" RESET, ARCHIVO);
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) > 0) {
            fprintf(archivo, "%s|%s|%s|%d\n",
                    lista[i].id,
                    lista[i].Producto,
                    lista[i].Marca,
                    lista[i].Cantidad);
        }
    }

    fclose(archivo);
}
void cargarDesdeArchivo() {
    crearCarpetaInventario(); // Asegurar que existe la carpeta
    FILE *archivo = fopen(ARCHIVO, "r");
    if (archivo == NULL) {
        printf(YELLOW "Creando nuevo archivo de inventario...\n" RESET);
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

//RF5: Búsqueda por ID, nombre, marca
int buscarPorID(Producto lista[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}
int buscarPorNombre(char nombre[]) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].Producto, nombre) == 0 && strlen(lista[i].id) > 0) {
            return i;
        }
    }
    return -1;
}
int buscarPorMarca(char marca[]) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].Marca, marca) == 0 && strlen(lista[i].id) > 0) {
            return i;
        }
    }
    return -1;
}

//RF1: Crear producto con confirmación y Valida si el ID único
int idUnico(char id[]) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].id, id) == 0 && strlen(lista[i].id) > 0) {
            return 0;
        }
    }
    return 1;
}
void crearProducto(Producto *p) {
    // Validación del ID (no vacío y único)
    while (1) {
        printf("Ingrese ID: ");
        fgets(p->id, 20, stdin);
        p->id[strcspn(p->id, "\n")] = '\0'; // Eliminar salto de línea

        if (strlen(p->id) == 0) {
            printf(RED "Error: El ID no puede estar vacío.\n" RESET);
        } else if (!idUnico(p->id)) {
            printf(RED "Error: ID ya existe. Intente nuevamente.\n" RESET);
        } else {
            break; // ID válido
        }
    }

    // Validación del nombre del producto (no vacío)
    while (1) {
        printf("Ingrese Producto: ");
        fgets(p->Producto, 50, stdin);
        p->Producto[strcspn(p->Producto, "\n")] = '\0';

        if (strlen(p->Producto) == 0) {
            printf(RED "Error: El nombre del producto no puede estar vacío.\n" RESET);
        } else {
            break; // Nombre válido
        }
    }

    // Validación de la marca (no vacía)
    while (1) {
        printf("Ingrese Marca: ");
        fgets(p->Marca, 50, stdin);
        p->Marca[strcspn(p->Marca, "\n")] = '\0';

        if (strlen(p->Marca) == 0) {
            printf(RED "Error: La marca no puede estar vacía.\n" RESET);
        } else {
            break; // Marca válida
        }
    }

    // Validación de Cantidad (no negativa)
   while (1) {
        printf("Ingrese Cantidad: ");
        scanf("%d", &p->Cantidad);
        getchar();  // Limpiar buffer

        if (p->Cantidad > 0) {
            break;
        } else {
            printf(RED "Error: La cantidad no puede ser negativa, ni 0.\nIntente nuevamente.\n" RESET);
        }
    }

    printf(GREEN "Producto agregado exitosamente.\n" RESET);
}

//RF6: Mostrar producto con alerta de bajo stock
void mostrarProducto(Producto p) {
    printf("\nID: %s\n", p.id);
    printf("Producto: %s\n", p.Producto);
    printf("Marca: %s\n", p.Marca);
    printf("Cantidad: %d\n", p.Cantidad);

    if (p.Cantidad <= 5) {
        printf(RED "ALERTA: Stock bajo!\n" RESET);
    }
}

//RF3: Eliminar producto
void eliminarProducto(Producto *p) {
    strcpy(p->id, "");
    strcpy(p->Producto, "");
    strcpy(p->Marca, "");
    p->Cantidad = 0;
}
int compararProductos(const void *a, const void *b) {
    const Producto *prodA = (const Producto *)a;
    const Producto *prodB = (const Producto *)b;
    return strcmp(prodA->Producto, prodB->Producto);
}
//RF4: Ordenar productos por nombre (orden alfabético)
void ordenarPorNombre() {
    qsort(lista, cantidad, sizeof(Producto), compararProductos);
}
void mostrarTablaProductos() {
    ordenarPorNombre();
    printf("\n+--------------+----------------------------------------+----------------------+-------------+\n");
    printf("|     ID       |             PRODUCTO                   |        MARCA         |   STOCK     |\n");
    printf("+--------------+----------------------------------------+----------------------+-------------+\n");
    int alertas = 0;
    int productosMostrados = 0;
    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) > 0) {
            // Resaltar en rojo si el stock es bajo (5 o menos)
            if (lista[i].Cantidad <= 5) {
                printf(RED);
                alertas++;
            }
            printf("| %-12s | %-38s | %-20s | %-11d |\n",
                   lista[i].id,
                   lista[i].Producto,
                   lista[i].Marca,
                   lista[i].Cantidad);
            printf(RESET); // Restablecer color

            productosMostrados++;
        }
    }
    printf("+--------------+----------------------------------------+----------------------+-------------+\n");
    printf("\nTotal de productos registrados: %d\n", cantidad);
    if (alertas > 0) {
        printf(RED "Alertas: %d producto(s) con stock bajo (5 unidades o menos)\n" RESET, alertas);
    }
    printf(" " RED "* Stock bajo o Producto agotado"RESET);
    printf(" * Stock normal\n");
}
//RF9:Editar producto existente
 void editarProducto(char id[]) {
    int pos = buscarPorID(lista, cantidad, id);
    if (pos == -1) {
        printf(RED "Error: Producto no encontrado.\n" RESET);
        return;
    }
    printf(CYAN "\nEditando producto ID: %s\n" RESET, lista[pos].id);
    // Editar nombre
    printf("Nombre actual: %s\nNuevo nombre (dejar vacio para mantener): ", lista[pos].Producto);
    char nuevoNombre[50];
    fgets(nuevoNombre, 50, stdin);
    nuevoNombre[strcspn(nuevoNombre, "\n")] = '\0';
    if (strlen(nuevoNombre) > 0) {
        strcpy(lista[pos].Producto, nuevoNombre);
    }
    // Editar marca
    printf("Marca actual: %s\nNueva marca (dejar vacio para mantener): ", lista[pos].Marca);
    char nuevaMarca[50];
    fgets(nuevaMarca, 50, stdin);
    nuevaMarca[strcspn(nuevaMarca, "\n")] = '\0';
    if (strlen(nuevaMarca) > 0) {
        strcpy(lista[pos].Marca, nuevaMarca);
    }
    // Editar cantidad
    printf("Cantidad actual: %d\nNueva cantidad (ingrese -1 para mantener): ", lista[pos].Cantidad);
    int nuevaCantidad;
    char input[10];
    fgets(input, 10, stdin);
    sscanf(input, "%d", &nuevaCantidad);
    if (nuevaCantidad >= 0) {
        lista[pos].Cantidad = nuevaCantidad;
    }
    guardarEnArchivo();
    printf(GREEN "¡Producto actualizado!\n" RESET);
}

//RF7: Registrar ventas con validación de stock
void registrarVenta() {
    char id[20];
    int cantidadVendida;
    printf("Ingrese ID del producto a vender: "); // Busca el Producto
    fgets(id, 20, stdin);
    id[strcspn(id, "\n")] = '\0';
    int pos = buscarPorID(lista, cantidad, id);
    if (pos == -1 || strlen(lista[pos].id) == 0) {
        printf(RED "\nError: Producto no encontrado.\n" RESET);
        return;
    }
    printf("Stock disponible: %d\n", lista[pos].Cantidad); // Validar stock disponible
    printf("Ingrese cantidad a vender: ");
    scanf("%d", &cantidadVendida);
    getchar();

    if (cantidadVendida <= 0) {
        printf(RED "\nError: Cantidad no valida.\n" RESET);
        return;
    }
    if (cantidadVendida > lista[pos].Cantidad) {
        printf(RED "\nError: Stock insuficiente.\n" RESET); //Verificación crítica de stock
        printf("Intento vender: %d | Stock disponible: %d\n",
               cantidadVendida, lista[pos].Cantidad);
        return; // Salir sin registrar venta
    }
    lista[pos].Cantidad -= cantidadVendida;     //Procesar venta (solo si pasa todas las validaciones)

    // Registrar en archivo de ventas
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char fecha[30];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", tm_info);
    FILE *ventas = fopen(ARCHIVO_VENTAS, "a");
    if (ventas != NULL) {
        fprintf(ventas, "%s|%s|%d|%s\n",
                lista[pos].id,
                lista[pos].Producto,
                cantidadVendida,
                fecha);
        fclose(ventas);

        printf(GREEN "\nVenta registrada exitosamente!\n" RESET);
        printf("Nuevo stock: %d\n", lista[pos].Cantidad);
    } else {
        printf(RED "\nError al guardar la venta.\n" RESET);
        // Revertir la reducción de stock si no se pudo guardar
        lista[pos].Cantidad += cantidadVendida;
    }
    guardarEnArchivo(); // Actualizar inventario
}

// RF8: Mostrar las ventas realizadas hoy y el total de productos vendidos
void mostrarVentasDelDia() {
    FILE *ventas = fopen(ARCHIVO_VENTAS, "r");
    if (ventas == NULL) {
        printf(RED "No hay registro de ventas.\n" RESET);
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
            printf("Producto: %s | Cantidad: %d | Fecha: %s\n",
                   v.Producto, v.CantidadVendida, v.fecha);
            totalVendidos += v.CantidadVendida;
        }
    }
    printf("-----------------------------------\n");
    printf("Total productos vendidos hoy: %d\n", totalVendidos);
    fclose(ventas);
}
// Limpieza de la consola de comandos
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Menu principal
//Menu principal
int main() {
    int opcion;
    char buffer[50];

    cargarDesdeArchivo();

    while (1) {
        printf(GREEN "UNIVERSIDAD DE LAS FUERZAS ARMADAS *ESPE*\n" RESET);
        printf(CYAN "FUNDAMENTOS_DE_PROGRAMACION" RESET);
        printf(GREEN "\n=== SISTEMA DE INVENTARIO ===\n" RESET);
        printf("1. Agregar Productos\n");
        printf("2. Mostrar Productos (Ordenados)\n");
        printf("3. Buscar Producto\n");  // Cambié aquí el texto para buscar unificado
        printf("4. Eliminar Producto\n");
        printf("5. Editar Producto\n");
        printf("6. Registrar Venta\n");
        printf("7. Ver Ventas del Dia\n");
        printf("8. Salir\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) {
            case 1:
                if (cantidad < MAX_PRODUCTOS) {
                    crearProducto(&lista[cantidad]);
                    cantidad++;
                    guardarEnArchivo();
                } else {
                    printf(RED "Limite de productos alcanzado.\n" RESET);
                }
                break;

            case 2:
                mostrarTablaProductos();
                break;

            case 3: {
                int subopcion;
                printf(CYAN "Buscar por:\n"RESET);
                printf("1. Nombre\n");
                printf("2. Marca\n");
                printf("3. ID\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &subopcion);
                getchar();

                int pos = -1;
                switch(subopcion) {
                    case 1:
                        printf("Ingrese el nombre del producto: ");
                        fgets(buffer, 50, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        pos = buscarPorNombre(buffer);
                        if (pos != -1) {
                            printf(GREEN "El Producto buscado es: "RESET);
                            mostrarProducto(lista[pos]);
                        } else {
                            printf(RED "Producto no encontrado.\n" RESET);
                        }
                        break;

                    case 2:
                        printf("Ingrese la marca a buscar: ");
                        fgets(buffer, 50, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        pos = buscarPorMarca(buffer);
                        if (pos != -1) {
                            printf(GREEN "El Producto buscado es: "RESET);
                            mostrarProducto(lista[pos]);
                        } else {
                            printf(RED "Marca no encontrada.\n" RESET);
                        }
                        break;

                    case 3:
                        printf("Ingrese el ID del producto: ");
                        fgets(buffer, 20, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        pos = buscarPorID(lista, cantidad, buffer);
                        if (pos != -1 && strlen(lista[pos].id) > 0) {
                            printf(GREEN "El Producto buscado es: "RESET);
                            mostrarProducto(lista[pos]);
                        } else {
                            printf(RED "Producto no encontrado.\n" RESET);
                        }
                        break;

                    default:
                        printf(RED "Opcion invalida.\n" RESET);
                }
                break;
            }

            case 4: {
                printf("Ingrese el ID del producto a eliminar: ");
                fgets(buffer, 20, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                int posEliminar = buscarPorID(lista, cantidad, buffer);
                if (posEliminar != -1 && strlen(lista[posEliminar].id) > 0) {
                    printf(YELLOW "\n=== CONFIRMACION DE ELIMINACION ===\n" RESET);
                    printf(CYAN "Producto a eliminar:\n" RESET);
                    mostrarProducto(lista[posEliminar]);
                    printf(RED "\nADVERTENCIA:*Esta accion no se puede deshacer*\n" RESET);
                    printf(YELLOW "Escriba 'ELIMINAR-%s\n" RESET, buffer);
                    char confirmacion[30];
                    fgets(confirmacion, 30, stdin);
                    confirmacion[strcspn(confirmacion, "\n")] = '\0';
                    char confirmacionEsperada[30];
                    sprintf(confirmacionEsperada, "ELIMINAR-%s", buffer);

                    if (strcmp(confirmacion, confirmacionEsperada) == 0) {
                        eliminarProducto(&lista[posEliminar]);
                        guardarEnArchivo();
                        printf(GREEN "\nProducto eliminado.\n" RESET);
                    } else {
                        printf(YELLOW "\nConfirmacion fallida. No se elimino.\n" RESET);
                    }
                } else {
                    printf(RED "Producto no encontrado.\n" RESET);
                }
                break;
            }

            case 5:
                printf("Ingrese ID del producto a editar: ");
                fgets(buffer, 20, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                editarProducto(buffer);
                break;

            case 6:
                registrarVenta();
                break;

            case 7:
                mostrarVentasDelDia();
                break;

            case 8:
                printf("Saliendo...\n");
                printf(GREEN "Creditos: Adriana Astudillo, Sarahi Munoz, Alan Nero :)" RESET);
                return 0;

            default:
                printf(RED "Opcion no valida.\n" RESET);
        }

        printf("\nPresione Enter para continuar...");
        getchar();
        limpiarPantalla();
    }

    return 0;
}
