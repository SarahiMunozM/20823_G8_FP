#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

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
#define ARCHIVO_BACKUP CARPETA_INVENTARIO "backup_inventario.txt"

// Estructura para almacenar información de productos
typedef struct {
    char id[20];
    char Producto[50];
    char Marca[50];
    int Cantidad;
    float Precio;
} Producto;

// Estructura para el registro de ventas
typedef struct {
    char id[20];
    char Producto[50];
    int CantidadVendida;
    float PrecioUnitario;
    float Total;
    char fecha[30];
} Venta;

Producto lista[MAX_PRODUCTOS];
int cantidad = 0;

// RF2: Guardar productos en archivo y Cargar productos desde archivo
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
    int i = 0;
    while (i < cantidad) {
        if (strlen(lista[i].id) > 0) {
            fprintf(archivo, "%s|%s|%s|%d|%.2f\n",
                    lista[i].id,
                    lista[i].Producto,
                    lista[i].Marca,
                    lista[i].Cantidad,
                    lista[i].Precio);
        }
        i++;
    }

    fclose(archivo);
}

void cargarDesdeArchivo() {
    crearCarpetaInventario();
    FILE *archivo = fopen(ARCHIVO, "r");
    if (archivo == NULL) {
        printf(YELLOW "Creando nuevo archivo de inventario...\n" RESET);
        return;
    }
    while (!feof(archivo) && cantidad < MAX_PRODUCTOS) {
        if (fscanf(archivo, "%[^|]|%[^|]|%[^|]|%d|%f\n",
                  lista[cantidad].id,
                  lista[cantidad].Producto,
                  lista[cantidad].Marca,
                  &lista[cantidad].Cantidad,
                  &lista[cantidad].Precio) == 5) {
            cantidad++;
        }
    }
    fclose(archivo);
}

// RF5: Búsqueda por ID, nombre, marca
int buscarPorID(Producto lista[], int n, char id[]) {
    int i = 0;
    while (i < n) {
        if (strcmp(lista[i].id, id) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

int buscarPorNombre(char nombre[]) {
    int i = 0;
    while (i < cantidad) {
        if (strcmp(lista[i].Producto, nombre) == 0 && strlen(lista[i].id) > 0) {
            return i;
        }
        i++;
    }
    return -1;
}

int buscarPorMarca(char marca[]) {
    int i = 0;
    while (i < cantidad) {
        if (strcmp(lista[i].Marca, marca) == 0 && strlen(lista[i].id) > 0) {
            return i;
        }
        i++;
    }
    return -1;
}

// RF1: Crear producto con confirmación y Valida si el ID único
int idUnico(char id[]) {
    for(int i = 0; i < cantidad; i++) {
        if(strcmp(lista[i].id, id) == 0 && strlen(lista[i].id) > 0) {
            return 0;
        }
    }
    return 1;
}

void crearProducto(Producto *p) {
    // Validación del ID (no vacío y único)
    printf("Ingrese ID: ");
    fgets(p->id, 20, stdin);
    p->id[strcspn(p->id, "\n")] = '\0';

    if(strlen(p->id) == 0) {
        printf(RED "Error: El ID no puede estar vacío. Operación cancelada.\n" RESET);
        return;
    }

    if(!idUnico(p->id)) {
        printf(RED "Error: ID ya existe. Operación cancelada.\n" RESET);
        return;
    }

    // Validación del nombre del producto (no vacío)
       while(1) {
        printf("Ingrese Producto: ");
        fgets(p->Producto, 50, stdin);
        p->Producto[strcspn(p->Producto, "\n")] = '\0';

        if(strlen(p->Producto) == 0) {
            printf(RED "Error: El nombre no puede estar vacío.\n" RESET);
        } else {
            break;
        }
    }

    // Validación de la marca (no vacía)
    while (1) {
        printf("Ingrese Marca: ");
        fgets(p->Marca, 50, stdin);
        p->Marca[strcspn(p->Marca, "\n")] = '\0';

        if (strlen(p->Marca) == 0) {
            printf(RED "Error: La marca no puede estar vacia.\n" RESET);
        } else {
            break;
        }
    }

    // Validación de Cantidad (no negativa)
    while (1) {
        printf("Ingrese Cantidad: ");
        int cantidadIngresada;
        if (scanf("%d", &cantidadIngresada) != 1) {
            printf(RED "Error: Ingrese un numero valido.\n" RESET);
            while (getchar() != '\n'); // Limpiar buffer
            continue;
        }
        getchar(); // Limpiar buffer

        if (cantidadIngresada > 0) {
            p->Cantidad = cantidadIngresada;
            break;
        } else {
            printf(RED "Error: La cantidad no puede ser negativa, ni 0.\nIntente nuevamente.\n" RESET);
        }
    }
    // Validación de Precio
    while (1) {
        printf("Ingrese Precio (USD): ");
        float precioIngresado;
        if (scanf("%f", &precioIngresado) != 1) {
            printf(RED "Error: Ingrese un numero valido.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        getchar();

        if (precioIngresado > 0) {
            p->Precio = precioIngresado;
            break;
        } else {
            printf(RED "Error: El precio debe ser mayor que 0.\n" RESET);
        }
    }

    printf(GREEN "Producto agregado exitosamente.\n" RESET);
}

// RF6: Mostrar producto con alerta de bajo stock
void mostrarProducto(Producto p) {
    printf("\nID: %s\n", p.id);
    printf("Producto: %s\n", p.Producto);
    printf("Marca: %s\n", p.Marca);
    printf("Cantidad: %d\n", p.Cantidad);
    printf("Precio: %f\n", p.Precio);

    if (p.Cantidad <= 5) {
        printf(RED "ALERTA: Stock bajo!\n" RESET);
    }
}

// RF3: Eliminar producto
void eliminarProducto(Producto *p) {
    p->id[0] = '\0';
    p->Producto[0] = '\0';
    p->Marca[0] = '\0';
    p->Precio = 0.0;
    p->Cantidad = 0;
}

int compararProductos(const void *a, const void *b) {
    const Producto *prodA = (const Producto *)a;
    const Producto *prodB = (const Producto *)b;
    return strcmp(prodA->Producto, prodB->Producto);
}

// RF4: Ordenar productos por nombre (orden alfabético)
void ordenarPorNombre() {
    qsort(lista, cantidad, sizeof(Producto), compararProductos);
}

void mostrarTablaProductos() {
    ordenarPorNombre();
    printf("\n+--------------+----------------------------------------+----------------------+-------------+-------------+\n");
    printf("|     ID       |             PRODUCTO                   |        MARCA         |   STOCK     |   Precio    |\n");
    printf("+--------------+----------------------------------------+----------------------+-------------+-------------+\n");

    int i = 0, alertas = 0, productosMostrados = 0;
    while (i < cantidad) {
        if (strlen(lista[i].id) > 0) {
            if (lista[i].Cantidad <= 5) {
                printf(RED);
                alertas++;
            }
            printf("| %-12s | %-38s | %-20s | %-11d | %-11.2f |\n",
                   lista[i].id,
                   lista[i].Producto,
                   lista[i].Marca,
                   lista[i].Cantidad,
                   lista[i].Precio);
            printf(RESET);
            productosMostrados++;
        }
        i++;
    }

    printf("+--------------+----------------------------------------+----------------------+-------------+-------------+\n");
    printf("\nTotal de productos registrados: %d\n", cantidad);
    if (alertas > 0) {
        printf(RED "Alertas: %d producto(s) con stock bajo (5 unidades o menos)\n" RESET, alertas);
    }
    printf(" " RED "* Stock bajo o Producto agotado" RESET);
    printf(" * Stock normal\n");
}

// RF9: Editar producto existente
void editarProducto(char id[]) {
    int pos = buscarPorID(lista, cantidad, id);
    if (pos == -1) {
        printf(RED "Error: Producto no encontrado.\n" RESET);
        return;
    }

    printf(CYAN "\nEditando producto ID: %s\n" RESET, lista[pos].id);

    // Editar nombre
    while (1) {
        printf("Nombre actual: %s\nNuevo nombre (dejar vacio para mantener): ", lista[pos].Producto);
        char nuevoNombre[50];
        fgets(nuevoNombre, 50, stdin);
        nuevoNombre[strcspn(nuevoNombre, "\n")] = '\0';
        if (strlen(nuevoNombre) > 0) {
            strcpy(lista[pos].Producto, nuevoNombre);
            break;
        } else {
            break;
        }
    }

    // Editar marca
    while (1) {
        printf("Marca actual: %s\nNueva marca (dejar vacio para mantener): ", lista[pos].Marca);
        char nuevaMarca[50];
        fgets(nuevaMarca, 50, stdin);
        nuevaMarca[strcspn(nuevaMarca, "\n")] = '\0';
        if (strlen(nuevaMarca) > 0) {
            strcpy(lista[pos].Marca, nuevaMarca);
            break;
        } else {
            break;
        }
    }

    // Editar cantidad
    while (1) {
        printf("Cantidad actual: %d\nNueva cantidad (ingrese -1 para mantener): ", lista[pos].Cantidad);
        char input[10];
        fgets(input, 10, stdin);
        int nuevaCantidad;
        if (sscanf(input, "%d", &nuevaCantidad) != 1) {
            printf(RED "Error: Ingrese un numero valido.\n" RESET);
            continue;
        }

        if (nuevaCantidad == -1) {
            break;
        } else if (nuevaCantidad >= 0) {
            lista[pos].Cantidad = nuevaCantidad;
            break;
        } else {
            printf(RED "Error: La cantidad no puede ser negativa.\n" RESET);
        }
    }

    // Editar Precio - CORRECCIÓN IMPORTANTE
    while (1) {
        printf("Precio actual: %.2f\nNuevo precio (ingrese -1 para mantener): ", lista[pos].Precio);
        char input[20];
        fgets(input, 20, stdin);
        float nuevoPrecio;
        if (sscanf(input, "%f", &nuevoPrecio) != 1) {
            printf(RED "Error: Ingrese un numero valido.\n" RESET);
            continue;
        }

        if (nuevoPrecio == -1) {
            break;
        } else if (nuevoPrecio >= 0) {
            lista[pos].Precio = nuevoPrecio;
            break;
        } else {
            printf(RED "Error: El precio no puede ser negativo.\n" RESET);
        }
    }

    guardarEnArchivo();
    printf(GREEN "¡Producto actualizado!\n" RESET);
}

// RF7: Registrar ventas con validación de stock
void registrarVenta() {
    char id[20];
    printf("Ingrese ID del producto a vender: ");
    fgets(id, 20, stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = buscarPorID(lista, cantidad, id);
    if (pos == -1 || strlen(lista[pos].id) == 0) {
        printf(RED "\nError: Producto no encontrado.\n" RESET);
        return;
    }

    printf("Stock disponible: %d\n", lista[pos].Cantidad);

    int cantidadVendida;
    while (1) {
        printf("Ingrese cantidad a vender: ");
        if (scanf("%d", &cantidadVendida) != 1) {
            printf(RED "Error: Ingrese un numero valido.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        getchar();

        if (cantidadVendida <= 0) {
            printf(RED "\nError: Cantidad no valida.\n" RESET);
        } else if (cantidadVendida > lista[pos].Cantidad) {
            printf(RED "\nError: Stock insuficiente.\n" RESET);
            printf("Intento vender: %d | Stock disponible: %d\n",
                   cantidadVendida, lista[pos].Cantidad);
        } else {
            break;
        }
    }
    float precioUnitario = lista[pos].Precio;
    float totalVenta = precioUnitario * cantidadVendida;

    lista[pos].Cantidad -= cantidadVendida;

    // Registrar en archivo de ventas
        time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char fecha[30];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", tm_info);

    FILE *ventas = fopen(ARCHIVO_VENTAS, "a");
    if (ventas != NULL) {
        fprintf(ventas, "%s|%s|%d|%.2f|%.2f|%s\n",
                lista[pos].id,
                lista[pos].Producto,
                cantidadVendida,
                precioUnitario,
                totalVenta,
                fecha);
        fclose(ventas);

        printf(GREEN "\nVenta registrada exitosamente!\n" RESET);
        printf("\n--- TICKET DE VENTA ---\n");
        printf("Producto: %s\nCantidad: %d\nPrecio: $%.2f\nTotal: $%.2f\nFecha: %s\n",
               lista[pos].Producto, cantidadVendida, precioUnitario, totalVenta, fecha);
        printf("-----------------------\n");
        printf("Nuevo stock: %d\n", lista[pos].Cantidad);
    } else {
        printf(RED "\nError al guardar la venta.\n" RESET);
        lista[pos].Cantidad += cantidadVendida;
    }
    guardarEnArchivo();
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

    char linea[256];
    int totalVendidos = 0;
    float totalVentas = 0.0;

    while (fgets(linea, sizeof(linea), ventas) != NULL) {
        Venta v;
        if (sscanf(linea, "%[^|]|%[^|]|%d|%f|%f|%[^\n]",
                   v.id, v.Producto, &v.CantidadVendida, &v.PrecioUnitario, &v.Total, v.fecha) == 6) {
            if (strncmp(v.fecha, fechaActual, 10) == 0) {
                printf("Producto: %s | Cantidad: %d | Total: $%.2f | Fecha: %s\n",
                       v.Producto, v.CantidadVendida, v.Total, v.fecha);
                totalVendidos += v.CantidadVendida;
                totalVentas += v.Total;
            }
        }
    }
    fclose(ventas);
    printf("-----------------------------------\n");
    printf("Total productos vendidos hoy: %d\n", totalVendidos);
    printf(GREEN "Total ganancias hoy: $%.2f\n" RESET, totalVentas);
}

// Limpieza de la consola de comandos
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Menú principal
int main() {
    cargarDesdeArchivo();
    bool salir = false;

    while (!salir) {
        limpiarPantalla();
        printf(GREEN "UNIVERSIDAD DE LAS FUERZAS ARMADAS *ESPE*\n" RESET);
        printf(CYAN "FUNDAMENTOS_DE_PROGRAMACION" RESET);
        printf(GREEN "\n=== SISTEMA DE INVENTARIO ===\n" RESET);
        printf("1. Agregar Productos\n");
        printf("2. Mostrar Productos (Ordenados)\n");
        printf("3. Buscar Producto\n");
        printf("4. Eliminar Producto\n");
        printf("5. Editar Producto\n");
        printf("6. Registrar Venta\n");
        printf("7. Ver Ventas del Dia\n");
        printf("8. Salir\n");

        int opcion;
        char input[10];
        printf("Seleccione una opcion: ");
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%d", &opcion) != 1) {
            printf(RED "\nError: Opcion no valida.\n" RESET);
            printf("\nPresione Enter para continuar...");
            getchar();
            continue;
        }

        switch(opcion) {
            case 1: {
                if (cantidad < MAX_PRODUCTOS) {
                    crearProducto(&lista[cantidad]);
                    cantidad++;
                    guardarEnArchivo();
                } else {
                    printf(RED "Limite de productos alcanzado.\n" RESET);
                }
                break;
            }

            case 2: {
                mostrarTablaProductos();
                break;
            }

            case 3: {
                int subopcion;
                printf(CYAN "Buscar por:\n" RESET);
                printf("1. Nombre\n");
                printf("2. Marca\n");
                printf("3. ID\n");
                printf("Seleccione una opcion: ");

                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &subopcion) != 1) {
                    printf(RED "Opción no valida.\n" RESET);
                    break;
                }

                char buffer[50];
                int pos = -1;

                switch(subopcion) {
                    case 1:
                        printf("Ingrese el nombre del producto: ");
                        fgets(buffer, 50, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        pos = buscarPorNombre(buffer);
                        break;

                    case 2:
                        printf("Ingrese la marca a buscar: ");
                        fgets(buffer, 50, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        pos = buscarPorMarca(buffer);
                        break;

                    case 3:
                        printf("Ingrese el ID del producto: ");
                        fgets(buffer, 20, stdin);
                        buffer[strcspn(buffer, "\n")] = '\0';
                        pos = buscarPorID(lista, cantidad, buffer);
                        break;

                    default:
                        printf(RED "Opcion invalida.\n" RESET);
                }

                if (pos != -1) {
                    printf(GREEN "El Producto buscado es: " RESET);
                    mostrarProducto(lista[pos]);
                } else {
                    printf(RED "No se encontro el producto.\n" RESET);
                }
                break;
            }

            case 4: {
                printf("Ingrese el ID del producto a eliminar: ");
                char buffer[20];
                fgets(buffer, 20, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                int posEliminar = buscarPorID(lista, cantidad, buffer);
                if (posEliminar != -1 && strlen(lista[posEliminar].id) > 0) {
                    printf(YELLOW "\n=== CONFIRMACION DE ELIMINACION ===\n" RESET);
                    printf(CYAN "Producto a eliminar:\n" RESET);
                    mostrarProducto(lista[posEliminar]);
                    printf(RED "\nADVERTENCIA:*Esta accion no se puede deshacer*\n" RESET);
                    printf(YELLOW "Escriba 'ELIMINAR-%s'\n" RESET, buffer);

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

            case 5: {
                printf("Ingrese ID del producto a editar: ");
                char buffer[20];
                fgets(buffer, 20, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                editarProducto(buffer);
                break;
            }

            case 6: {
                registrarVenta();
                break;
            }

            case 7: {
                mostrarVentasDelDia();
                break;
            }

            case 8: {
                printf("Saliendo...\n");
                printf(GREEN "Creditos: Adriana Astudillo, Sarahi Munoz, Alan Nero :)" RESET);
                salir = true;
                break;
            }

            default: {
                printf(RED "Opcion no valida.\n" RESET);
            }
        }

        if (!salir) {
            printf("\nPresione Enter para continuar...");
            while (getchar() != '\n'); // Limpiar buffer y esperar Enter
        }
    }

    return 0;
}
