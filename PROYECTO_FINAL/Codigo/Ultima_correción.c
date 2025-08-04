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
#define MAGENTA "\x1b[35m"
#define ORANGE  "\x1B[38;2;255;128;0m"
#define LBLUE   "\x1B[38;2;53;149;240m"
#define RESET "\x1b[0m"

#define MAX_NOMBRE 50
#define MAX_PRODUCTOS 10000
#define BUSCAR_POR_ID 1
#define BUSCAR_POR_NOMBRE 2
#define BUSCAR_POR_MARCA 3
#define CARPETA_INVENTARIO "inventario/"
#define ARCHIVO CARPETA_INVENTARIO "datos_inventario.txt"
#define ARCHIVO_VENTAS CARPETA_INVENTARIO "registro_ventas.txt"
#define ARCHIVO_BACKUP CARPETA_INVENTARIO "backup_inventario.txt"

// Estructura para almacenar información de productos
typedef struct {
    char id[20];
    char Producto[50];
    char Marca[50];
    char Proveedor[50];
    int Cantidad;
    float Precio;
    int Estado;
    int EnPausa;
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

void mostrarProducto(Producto p);
void mostrarResultadosBusqueda(int tipo, const char *termino);
int buscarProducto(int tipoBusqueda, const char *valor);
int buscarPorID(Producto lista[], int cantidad, const char *id);

// RF2: Guardar productos en archivo y Cargar productos desde archivo
void crearCarpetaInventario() {
    #ifdef _WIN32
        system("mkdir inventario 2> nul");
    #else
        system("mkdir -p inventario");
    #endif
}
// Limpieza de la consola de comandos
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void guardarEnArchivo() {
    FILE *archivo = fopen(ARCHIVO, "wb");
    if (archivo == NULL) {
        printf(RED "Error: No se pudo abrir %s\n" RESET, ARCHIVO);
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) > 0) {
            fprintf(archivo, "%s|%s|%s|%s|%d|%.2f|%d|%d\n",
                    lista[i].id,
                    lista[i].Producto,
                    lista[i].Marca,
                    lista[i].Proveedor,
                    lista[i].Cantidad,
                    lista[i].Precio,
                    lista[i].Estado,
                    lista[i].EnPausa);
        }
    }

    fclose(archivo);
}

void cargarDesdeArchivo() {
    crearCarpetaInventario();
    FILE *archivo = fopen(ARCHIVO, "r");
    printf(ORANGE "==== PROCESO DE CREACION Y VERIFICACION DE LA CARPETA INVENTARIO ==== \n"RESET);
    if (!archivo) {
        printf(YELLOW "Archivo de inventario no encontrado. Se creará uno nuevo.\n" RESET);
        printf("Presione Enter para continuar...");
        getchar();
        return;
    }

    cantidad = 0;
    char linea[256];
    int errores = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';
        if (strlen(linea) == 0) continue;

        Producto p = {0};
        int campos_leidos = sscanf(linea, "%19[^|]|%49[^|]|%49[^|]|%49[^|]|%d|%f|%d|%d",
                                 p.id, p.Producto, p.Marca, p.Proveedor,
                                 &p.Cantidad, &p.Precio, &p.Estado, &p.EnPausa);

        if (campos_leidos >= 5) {
            if (campos_leidos < 6) p.Precio = 0.0f;
            if (campos_leidos < 7) p.Estado = 1;
            if (campos_leidos < 8) p.EnPausa = 0;

            if (strlen(p.Proveedor) == 0) {
                strcpy(p.Proveedor, "Sin proveedor");
            }

            lista[cantidad++] = p;
        } else {
            printf(RED "\nError en línea: %s\n" RESET, linea);
            errores++;
        }
    }

    fclose(archivo);

    if (errores > 0) {
        printf(RED "Se encontraron %d errores en el archivo.\n" RESET, errores);
        printf("Algunos productos pueden no haberse cargado correctamente.\n");
    } else {
        printf(GREEN "Inventario cargado correctamente. %d productos registrados.\n" RESET, cantidad);
    }
        printf("Presione Enter para continuar...");
    getchar();
}

// RF6: Búsqueda por ID, nombre, marca
int buscarProducto(int tipoBusqueda, const char *valor) {
    for(int i = 0; i < cantidad; i++) {
        if(strlen(lista[i].id) == 0) continue;

        switch(tipoBusqueda) {
            case BUSCAR_POR_ID:
                if(strcmp(lista[i].id, valor) == 0) return i;
                break;
            case BUSCAR_POR_NOMBRE:
                if(strcmp(lista[i].Producto, valor) == 0) return i;
                break;
            case BUSCAR_POR_MARCA:
                if(strcmp(lista[i].Marca, valor) == 0) return i;
                break;
        }
    }
    return -1;
}
void mostrarResultadosBusqueda(int tipo, const char *termino) {
    printf(CYAN "\n=== RESULTADOS DE BUSQUEDA ===\n" RESET);

    int encontrados = 0;
    for(int i = 0; i < cantidad; i++) {
        if(strlen(lista[i].id) == 0) continue;

        bool coincide = false;
        switch(tipo) {
            case BUSCAR_POR_ID: coincide = (strcmp(lista[i].id, termino) == 0); break;
            case BUSCAR_POR_NOMBRE: coincide = (strstr(lista[i].Producto, termino) != NULL); break;
            case BUSCAR_POR_MARCA: coincide = (strstr(lista[i].Marca, termino) != NULL); break;
        }

        if(coincide) {
            mostrarProducto(lista[i]);  // Ahora está declarada
            encontrados++;
        }
    }

    if(encontrados == 0) {
        printf(RED "No se encontraron productos.\n" RESET);
    } else {
        printf(GREEN "\nTotal encontrados: %d\n" RESET, encontrados);
    }
}

// RF2: Crear producto con confirmación y Valida si el ID único
int idUnico(char id[]) {
    for(int i = 0; i < cantidad; i++) {
        if(strcmp(lista[i].id, id) == 0 && strlen(lista[i].id) > 0) {
            return 0;
        }
    }
    return 1;
}

void crearProducto(Producto *p) {
    Producto temp;
    printf(MAGENTA "==== PROCESO DE CREACION DE UN PRODUCTO EN EL INVENTARIO ====\n"RESET);
    // Validación del ID (no vacío y único)
    printf("\nIngrese ID: ");
    fgets(temp.id, 20, stdin);
    temp.id[strcspn(temp.id, "\n")] = '\0';

    if(strlen(temp.id) == 0) {
        printf(RED "Error: El ID no puede estar vacio. Operacion cancelada.\n" RESET);
        return;
    }

    if(!idUnico(temp.id)) {
        printf(RED "Error: ID ya existe. Operacion cancelada.\n" RESET);
        return;
    }

    // Validación del Nombre
    do {
        printf("Ingrese Nombre del producto (requerido): ");
        fgets(temp.Producto, 50, stdin);
        temp.Producto[strcspn(temp.Producto, "\n")] = '\0';

        if (strlen(temp.Producto) == 0) {
            printf(RED "Error: El nombre es obligatorio.\n" RESET);
        }
    } while (strlen(temp.Producto) == 0);

    // Validación de la Marca
    do {
        printf("Ingrese Marca (requerido): ");
        fgets(temp.Marca, 50, stdin);
        temp.Marca[strcspn(temp.Marca, "\n")] = '\0';

        if (strlen(temp.Marca) == 0) {
            printf(RED "Error: La marca es obligatoria.\n" RESET);
        }
    } while (strlen(temp.Marca) == 0);

    // Validación de cantidad (permite 0)
    char input[50];
    while (1) {
        printf("Ingrese cantidad (≥ 0): ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &temp.Cantidad) == 1 && temp.Cantidad >= 0) {
            break;
        }
        printf(RED "Error: Ingrese un numero valido.\n" RESET);
    }

    // Validación de precio
    while (1) {
        printf("Ingrese precio (> 0): ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%f", &temp.Precio) == 1 && temp.Precio > 0) {
            break;
        }
        printf(RED "Error: Ingrese un valor positivo.\n" RESET);
    }
    printf("¿Desea asignar un proveedor? (s/n): ");
    char opcion = tolower(getchar());
    while (getchar() != '\n');

    if (opcion == 's') {
        printf("Ingrese Proveedor: ");
        fgets(temp.Proveedor, 50, stdin);
        temp.Proveedor[strcspn(temp.Proveedor, "\n")] = '\0';

        if (strlen(temp.Proveedor) == 0) {
            printf(YELLOW "Advertencia: No se ingreso proveedor. Se asignara 'Sin proveedor'.\n" RESET);
            strcpy(temp.Proveedor, "Sin proveedor");
        }
    } else {
        strcpy(temp.Proveedor, "Sin proveedor");
    }
    temp.Estado = 1;
    temp.EnPausa = 0;

    // Confirmación final
    printf("\n" GREEN "=== RESUMEN DEL PRODUCTO ===" RESET "\n");
    printf("ID: %s\n", temp.id);
    printf("Nombre: %s\n", temp.Producto);
    printf("Marca: %s\n", temp.Marca);
    printf("Cantidad: %d\n", temp.Cantidad);
    printf("Precio: %.2f\n", temp.Precio);
    printf("Proveedor: %s\n", temp.Proveedor);

    printf("\n¿Confirmar creacion? (s/n): ");
    opcion = tolower(getchar());
    while (getchar() != '\n');

    if (opcion != 's') {
        printf(YELLOW "Creacion cancelada.\n" RESET);
        return;
    }
    *p = temp;
    printf(GREEN "\n¡Producto creado exitosamente!\n" RESET);
}

// RF6: Mostrar producto con alerta de bajo stock
void mostrarProducto(Producto p) {
    printf("\nID: %s\n", p.id);
    printf("Producto: %s\n", p.Producto);
    printf("Marca: %s\n", p.Marca);
    printf("Cantidad: %d\n", p.Cantidad);
    printf("Precio: %.2f\n", p.Precio);

    if(p.Cantidad <= 5) {
        printf(RED "ALERTA: Stock bajo!\n" RESET);
    }
}

// RF3: Eliminar producto
void eliminarProducto(int pos) {
    if (pos < 0 || pos >= cantidad) {
        printf(RED "Posición inválida.\n" RESET);
        return;
    }
    lista[pos].id[0] = '\0';
    guardarEnArchivo();
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

void mostrarTodosProductos() {
    ordenarPorNombre();

    printf(LBLUE "\n=== LISTA COMPLETA DE PRODUCTOS ===\n"RESET);
    printf("\n+--------------+----------------------------------------+----------------------+-------------+-------------+\n");
    printf("|     ID       |             PRODUCTO                   |        MARCA         |   STOCK     |   Precio    |\n");
    printf("+--------------+----------------------------------------+----------------------+-------------+-------------+\n");

    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) == 0) continue;

        printf("| %-12s | %-38s | %-20s | %-11d | %-11.2f |\n",
               lista[i].id,
               lista[i].Producto,
               lista[i].Marca,
               lista[i].Cantidad,
               lista[i].Precio);
    }
    printf("+--------------+----------------------------------------+----------------------+-------------+-------------+\n");
    printf("Total de productos: %d\n", cantidad);
}
// RF6: Tabla de producto con alerta de bajo stock
void mostrarAlertasStock() {
    int alertas = 0;

    printf(ORANGE "\n=== PRODUCTOS CON STOCK BAJO (<5 unidades) ===\n"RESET);
    printf(RED);
    printf("\n+--------------+----------------------------------------+----------------------+-------------+-------------+\n");
    printf("|     ID       |             PRODUCTO                   |        MARCA         |   STOCK     |   Precio    |\n");
    printf("+--------------+----------------------------------------+----------------------+-------------+-------------+\n");

    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) == 0) continue;

        if (lista[i].Cantidad <= 5) {
            printf("| %-12s | %-38s | %-20s | %-11d | %-11.2f |\n",
                   lista[i].id,
                   lista[i].Producto,
                   lista[i].Marca,
                   lista[i].Cantidad,
                   lista[i].Precio);
            alertas++;
        }
    }

    printf("+--------------+----------------------------------------+----------------------+-------------+-------------+\n");
    printf(RESET);
    printf("Total de alertas: %d\n", alertas);
}
// RF10: Muestra productos activos/inactivos
void mostrarEstadoRestock() {
    printf(LBLUE "\n=== ESTADO DE RE-STOCK ===" RESET);
    printf("\n+--------------+---------------------------------------+-----------------+--------+\n");
    printf("|     ID       |             PRODUCTO                  |       MARCA     | ESTADO |");
    printf("\n+--------------+---------------------------------------+-----------------+--------+\n");

    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) == 0) continue;

        printf("| %-12s | %-37s | %-15s | %-10s |\n",
               lista[i].id,
               lista[i].Producto,
               lista[i].Marca,
               lista[i].Estado ? GREEN "ACTIVO" RESET : RED "INACTIVO" RESET);
    }
    printf("+--------------+---------------------------------------+-----------------+--------+\n");
}

// RF11: Muestra productos en pausa por proveedores
void mostrarProductosEnPausa() {
    int enPausa = 0;

    printf(ORANGE "\n=== PRODUCTOS EN PAUSA POR PROVEEDORES ===\n" RESET);
    printf("+------------------+-----------------------------------+------------------+\n");
    printf("|    PROVEEDOR     |          PRODUCTO                 |       MARCA      |\n");
    printf("+------------------+-----------------------------------+------------------+\n");

    for (int i = 0; i < cantidad; i++) {
        if (strlen(lista[i].id) == 0 || !lista[i].EnPausa) continue;

        printf("| %-16s | %-33s | %-16s |\n",
               lista[i].Proveedor,
               lista[i].Producto,
               lista[i].Marca);
        enPausa++;
    }

    printf("+------------------+-----------------------------------+------------------+\n");
    if (enPausa == 0) {
        printf(GREEN "No hay productos en pausa por proveedores.\n" RESET);
    }
}

// RF4: Editar producto existente
void editarProducto(char id[]) {
    int pos = buscarProducto(BUSCAR_POR_ID, id);
    if (pos == -1) {
        printf(RED "\nError: Producto no encontrado.\n" RESET);
        printf("Presione Enter para continuar...");
        while(getchar() != '\n');
        return;
    }
    printf(CYAN "\n=== EDITANDO PRODUCTO ===\n" RESET);
    printf("ID: %s\n", lista[pos].id);

    int opcion;
    char input[50];

    do {
        // Menú compacto
        printf("\n%sCAMPOS EDITABLES:%s\n", YELLOW, RESET);
        printf("1. Nombre      [%s%s%s]\n", CYAN, lista[pos].Producto, RESET);
        printf("2. Marca       [%s%s%s]\n", CYAN, lista[pos].Marca, RESET);
        printf("3. Proveedor   [%s%s%s]\n", CYAN, lista[pos].Proveedor, RESET);
        printf("4. Cantidad    [%s%d%s]\n", CYAN, lista[pos].Cantidad, RESET);
        printf("5. Precio      [%s%.2f%s]\n", CYAN, lista[pos].Precio, RESET);
        printf("6. Estado      [%s%s%s]\n", CYAN, lista[pos].Estado ? "ACTIVO" : "INACTIVO", RESET);
        printf("7. Pausa       [%s%s%s]\n", CYAN, lista[pos].EnPausa ? "EN PAUSA" : "DISPONIBLE", RESET);
        printf("0. %sGuardar y salir%s\n", GREEN, RESET);
        printf("\nSeleccione campo a editar (0 / enter para terminar): ");

        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &opcion);

        switch(opcion) {
            case 1:
                printf("\nNombre actual: %s\nNuevo nombre: ", lista[pos].Producto);
                fgets(lista[pos].Producto, 50, stdin);
                lista[pos].Producto[strcspn(lista[pos].Producto, "\n")] = '\0';
                break;

            case 2:
                printf("\nMarca actual: %s\nNueva marca: ", lista[pos].Marca);
                fgets(lista[pos].Marca, 50, stdin);
                lista[pos].Marca[strcspn(lista[pos].Marca, "\n")] = '\0';
                break;

            case 3: // Editar proveedor
                printf("\nProveedor actual: %s\n", lista[pos].Proveedor);
                printf("Opciones:\n");
                printf("1. Modificar proveedor\n");
                printf("2. Eliminar proveedor (dejar sin proveedor)\n");
                printf("3. Mantener sin cambios\n");
                printf("Seleccione opción: ");

                fgets(input, sizeof(input), stdin);
                int opcionProveedor;
                sscanf(input, "%d", &opcionProveedor);

                switch(opcionProveedor) {
                    case 1:
                        printf("Nuevo proveedor: ");
                        fgets(lista[pos].Proveedor, 50, stdin);
                        lista[pos].Proveedor[strcspn(lista[pos].Proveedor, "\n")] = '\0';
                        break;

                    case 2:
                        strcpy(lista[pos].Proveedor, "Sin proveedor"); // O "" si prefieres
                        printf(GREEN "Proveedor eliminado.\n" RESET);
                        break;

                    case 3:
                        printf(YELLOW "Proveedor no modificado.\n" RESET);
                        break;

                        default:
                        printf(RED "Opción no válida. Proveedor no modificado.\n" RESET);
                        }
                        break;

            case 4:
                while(1) {
                    printf("\nCantidad actual: %d\nNueva cantidad: ", lista[pos].Cantidad);
                    fgets(input, sizeof(input), stdin);
                    if(sscanf(input, "%d", &lista[pos].Cantidad) == 1 && lista[pos].Cantidad >= 0) {
                        break;
                    }
                    printf(RED "Error: Cantidad inválida (debe ser ≥ 0)\n" RESET);
                }
                break;

            case 5:
                while(1) {
                    printf("\nPrecio actual: %.2f\nNuevo precio: ", lista[pos].Precio);
                    fgets(input, sizeof(input), stdin);
                    if(sscanf(input, "%f", &lista[pos].Precio) == 1 && lista[pos].Precio > 0) {
                        break;
                    }
                    printf(RED "Error: Precio inválido (debe ser > 0)\n" RESET);
                }
                break;

            case 6:
                lista[pos].Estado = !lista[pos].Estado;
                printf("\nEstado cambiado a: %s%s%s\n",
                       lista[pos].Estado ? GREEN : RED,
                       lista[pos].Estado ? "ACTIVO" : "INACTIVO",
                       RESET);
                break;

            case 7:
                lista[pos].EnPausa = !lista[pos].EnPausa;
                printf("\nEstado de pausa cambiado a: %s%s%s\n",
                       lista[pos].EnPausa ? YELLOW : GREEN,
                       lista[pos].EnPausa ? "EN PAUSA" : "DISPONIBLE",
                       RESET);
                break;

            case 0:
                guardarEnArchivo();
                printf(GREEN "\nCambios guardados exitosamente.\n" RESET);
                break;

            default:
                printf(RED "\nOpción no válida. Intente nuevamente.\n" RESET);
        }

        // Pausa breve después de cada operación
        if (opcion != 0) {
            printf("\nPresione Enter para continuar...");
            while(getchar() != '\n');
            limpiarPantalla();
            printf(CYAN "\nEditando: %s\n", lista[pos].Producto);
        }

    } while(opcion != 0);
}

// RF9: Registrar ventas con validación de stock
void registrarVenta() {
    char id[20];
    printf(ORANGE "==== REGISTRO DE VENTAS DE LOS PRODUCTOS DEL INVENTARIO ==== \n"RESET);
    printf("\nIngrese ID del producto a vender: ");
    fgets(id, 20, stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = buscarProducto(BUSCAR_POR_ID, id);
    if (pos == -1 || strlen(lista[pos].id) == 0) {
        printf(RED "\nError: Producto no encontrado.\n" RESET);
        getchar();
        return;
    }

    printf("\nStock disponible: %d\n", lista[pos].Cantidad);

    int cantidadVendida;
    while (1) {
        printf("Ingrese cantidad a vender (0 para cancelar): ");
        if (scanf("%d", &cantidadVendida) != 1) {
            printf(RED "\nError: Ingrese un número válido.\n" RESET);
            continue;
        }
        while(getchar() != '\n');

        if (cantidadVendida == 0) {
            printf(RED "Venta cancelada.\n" RESET);
            return;
        } else if (cantidadVendida < 0) {
            printf(RED "Error: La cantidad no puede ser negativa.\n" RESET);
        } else if (cantidadVendida > lista[pos].Cantidad) {
            printf(RED "Error: Stock insuficiente.\n" RESET);
            printf("\nIntento vender: %d | Stock disponible: %d\n",
                   cantidadVendida, lista[pos].Cantidad);
        } else {
            break;
        }
    }

    // Proceso de venta
    float precioUnitario = lista[pos].Precio;
    float totalVenta = precioUnitario * cantidadVendida;
    lista[pos].Cantidad -= cantidadVendida;

    // Registrar en archivo de ventas
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char fecha[30];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d %H:%M:%S", tm_info);

    FILE *ventas = fopen(ARCHIVO_VENTAS, "a");
    if (ventas == NULL) {
        printf(RED "\nError al guardar la venta.\n" RESET);
        lista[pos].Cantidad += cantidadVendida;
        guardarEnArchivo();
        printf("Presione Enter para volver al menu...");
        getchar();
        return;
    }

    fprintf(ventas, "%s|%s|%d|%.2f|%.2f|%s\n",
            lista[pos].id,
            lista[pos].Producto,
            cantidadVendida,
            precioUnitario,
            totalVenta,
            fecha);
    fclose(ventas);

    // Mostrar ticket
    printf(GREEN "\nVenta registrada exitosamente!\n" RESET);
    printf(MAGENTA"\n--- TICKET DE VENTA ---\n"RESET);
    printf("Producto: %s\nCantidad: %d\nPrecio: $%.2f\nTotal: $%.2f\nFecha: %s\n",
           lista[pos].Producto, cantidadVendida, precioUnitario, totalVenta, fecha);
    printf("-----------------------\n");
    printf("Nuevo stock: %d\n", lista[pos].Cantidad);

    guardarEnArchivo();
}
// RF8: Mostrar las ventas realizadas hoy y el total de productos vendidos
void mostrarVentasDelDia() {
    FILE *ventas = fopen(ARCHIVO_VENTAS, "r");
    printf(ORANGE "==== HISTORIAL DE VENTAS REALIZADAS ==== \n"RESET);
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
    printf("\nTotal productos vendidos hoy: %d\n", totalVendidos);
    printf(GREEN "\nTotal ganancias hoy: $%.2f\n" RESET, totalVentas);
}
void cambiarEstadoProducto() {
    char id[20];
    printf("Ingrese ID del producto: ");
    fgets(id, 20, stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = buscarProducto(BUSCAR_POR_ID, id);
    if (pos == -1) {
        printf(RED "Producto no encontrado!\n" RESET);
        return;
    }

    printf("\n1. Cambiar estado re-stock\n2. Cambiar estado pausa\nOpción: ");
    int op;
    scanf("%d", &op);
    getchar();

    if (op == 1) {
        lista[pos].Estado = !lista[pos].Estado;
        printf("Producto marcado como %s\n",
               lista[pos].Estado ? "ACTIVO" : "INACTIVO");
    } else if (op == 2) {
        lista[pos].EnPausa = !lista[pos].EnPausa;
        printf("Producto %s pausa\n",
               lista[pos].EnPausa ? "en" : "sin");
    }
    guardarEnArchivo();
}

// Menú principal
int main() {
    memset(lista, 0, sizeof(lista));
    cantidad = 0;
    cargarDesdeArchivo();
    bool salir = false;

    while (!salir) {
        limpiarPantalla();
        printf(GREEN "UNIVERSIDAD DE LAS FUERZAS ARMADAS *ESPE*\n" RESET);
        printf(CYAN "FUNDAMENTOS_DE_PROGRAMACION" RESET);
        printf(GREEN "\n=== SISTEMA DE INVENTARIO ===\n" RESET);
        printf("1. Agregar Productos\n");
        printf("2. Mostrar Todos los Productos\n");
        printf("3. Alertas de Stock Bajo\n");
        printf("4. Buscar Producto\n");
        printf("5. Eliminar Producto\n");
        printf("6. Editar Producto\n");
        printf("7. Registrar Venta\n");
        printf("8. Ver Ventas del Dia\n");
        printf("9. Estado de Re-stock\n");
        printf("10. Productos en Pausa\n");
        printf("11. Salir\n");

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
                limpiarPantalla();
                if (cantidad < MAX_PRODUCTOS) {
                    crearProducto(&lista[cantidad]);
                    cantidad++;
                    guardarEnArchivo();
                } else {
                    printf(RED "Limite de productos alcanzado.\n" RESET);
                }
                break;
                while(getchar() != '\n');
            }
            case 2:
                limpiarPantalla();
                mostrarTodosProductos();
                break;
                while(getchar() != '\n');
            case 3:
                limpiarPantalla();
                mostrarAlertasStock();
                break;
                while(getchar() != '\n');
            case 4: {
                limpiarPantalla();
                printf(LBLUE "==== PROCESO DE BUSQUEDA DEL PRODUCTO EN EL INVENTARIO ==== \n"RESET);
                printf(MAGENTA "\n=== TIPO DE BUSQUEDA ===" RESET);
                printf("\n1. Por ID");
                printf("\n2. Por Nombre");
                printf("\n3. Por Marca");
                printf("\nSeleccione: ");

                int tipoBusqueda;
                scanf("%d", &tipoBusqueda);
                while(getchar() != '\n');

                char valor[50];
                printf("\nIngrese termino de busqueda: ");
                fgets(valor, 50, stdin);
                valor[strcspn(valor, "\n")] = '\0';

                mostrarResultadosBusqueda(tipoBusqueda, valor);
                break;
                while(getchar() != '\n');
            }
            case 5: {
                limpiarPantalla();
                printf(LBLUE "==== PROCESO DE ELIMINACION DEL PRODUCTO EN EL INVENTARIO ==== \n"RESET);
                printf("Ingrese el ID del producto a eliminar: ");
                char buffer[20];
                fgets(buffer, 20, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                int posEliminar = buscarProducto(BUSCAR_POR_ID, buffer);

                if (posEliminar == -1) {
                    printf(RED "Error: Producto no encontrado.\n" RESET);
                } else {
                    // Mostrar información del producto antes de eliminar
                    printf(YELLOW "\n=== CONFIRMACION DE ELIMINACION ===\n" RESET);
                    printf(CYAN "\nProducto a eliminar:\n" RESET);
                    mostrarProducto(lista[posEliminar]);

                    // Sistema de confirmación
                    printf(RED "\nADVERTENCIA: Esta accion no se puede deshacer\n" RESET);
                    printf(YELLOW "Si esta seguro de eliminar escriba 'ELIMINAR-%s'\n" RESET, buffer);
                    printf("Confirmacion: ");

                    char confirmacion[30];
                    fgets(confirmacion, 30, stdin);
                    confirmacion[strcspn(confirmacion, "\n")] = '\0';

                    char confirmacionEsperada[30];
                    sprintf(confirmacionEsperada, "ELIMINAR-%s", buffer);

                    if (strcmp(confirmacion, confirmacionEsperada) == 0) {
                        eliminarProducto(posEliminar);
                        guardarEnArchivo();
                        printf(GREEN "\nProducto eliminado.\n" RESET);
                    } else {
                        printf(YELLOW "\nConfirmacion fallida. No se elimino.\n" RESET);
                    }
                }
                break;
                while(getchar() != '\n');
            }
            case 6: {
                limpiarPantalla();
                printf(ORANGE "==== PROCESO DE EDICION DEL PRODUCTO EN EL INVENTARIO ==== \n"RESET);
                printf("Ingrese ID del producto a editar: ");
                char buffer[20];
                fgets(buffer, 20, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                editarProducto(buffer);
                break;
                while(getchar() != '\n');
            }

            case 7: {
                limpiarPantalla();
                registrarVenta();
                break;
                while(getchar() != '\n');
            }

            case 8: {
                limpiarPantalla();
                mostrarVentasDelDia();
                break;
                while(getchar() != '\n');
            }
            case 9:
                limpiarPantalla();
                mostrarEstadoRestock();
                break;
            case 10:
                limpiarPantalla();
                mostrarProductosEnPausa();
                break;
                while(getchar() != '\n');

            case 11: {
                limpiarPantalla();
                printf(ORANGE "==== lOS DATOS SE HAN GURADADO EXITOSAMENTE EN EL INVENTARIO ==== \n"RESET);
                printf("Saliendo...\n");
                printf(GREEN "Creditos: Adriana Astudillo, Sarahi Munoz, Alan Nero :)" RESET);
                salir = true;
                break;
                while(getchar() != '\n');
            }

            default: {
                printf(RED "Opcion no valida.\n" RESET);
            }
        }

        if (!salir) {
            printf("\nPresione Enter para continuar...");
            while (getchar() != '\n');
        }
    }

    return 0;
}
