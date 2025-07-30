#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRLEN 256

int main() {
    int cantidadproductos = 0;
    int cantidadvendida;
    int cantidadventa[100];
    int cantidadventas = 0;
    char confirmacion[MAX_STRLEN];
    bool encontrado;
    char fechaventa[100][MAX_STRLEN];
    int i, j;
    int idbuscar;
    int idproducto[100];
    int idproductoventa[100];
    int idventa[100];
    char marcabuscar[MAX_STRLEN];
    char marcaproducto[100][MAX_STRLEN];
    char nombrebuscar[MAX_STRLEN];
    char nombreproducto[100][MAX_STRLEN];
    int opcion;
    float precioproducto[100];
    float stockproducto[100];

	cantidadproductos = 1;
	cantidadventas = 1;
    do {
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("1. Agregar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Buscar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Editar producto\n");
        printf("6. Registrar venta\n");
        printf("7. Ver Ventas del dia\n");
        printf("8. Salir\n");
        printf("Ingrese una opcion:\n");
        scanf("%i", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadproductos < 100) {
                    do {
                        printf("Ingrese ID del producto (entero positivo):\n");
                        scanf("%d", &idproducto[cantidadproductos]);
                        if (idproducto[cantidadproductos] <= 0)
                            printf("Error: ID invalido.\n");
                    } while (idproducto[cantidadproductos] <= 0);

                    printf("Ingrese nombre del producto:\n");
                    scanf("%s", nombreproducto[cantidadproductos]);

                    printf("Ingrese marca del producto:\n");
                    scanf("%s", marcaproducto[cantidadproductos]);

                    do {
                        printf("Ingrese precio del producto:\n");
                        scanf("%f", &precioproducto[cantidadproductos]);
                        if (precioproducto[cantidadproductos] <= 0)
                            printf("Error: Precio invalido.\n");
                    } while (precioproducto[cantidadproductos] <= 0);

                    do {
                        printf("Ingrese stock disponible:\n");
                        scanf("%f", &stockproducto[cantidadproductos]);
                        if (stockproducto[cantidadproductos] < 0)
                            printf("Error: Stock invalido.\n");
                    } while (stockproducto[cantidadproductos] < 0);

                    cantidadproductos++;
                    printf("Producto registrado con exito\n");
                } else {
                    printf("No hay espacio para mas productos.\n");
                }
                break;

		            case 2:
                if (cantidadproductos > 0) {
                    printf("=== LISTA DE PRODUCTOS ===\n");
                    for (i = 0; i < cantidadproductos; i++) {
                        printf("-----------------------------------\n");
                        printf("ID: %d\n", idproducto[i]);
                        printf("Nombre: %s\n", nombreproducto[i]);
                        printf("Marca: %s\n", marcaproducto[i]);
                        printf("Precio: $%.2f\n", precioproducto[i]);
                        printf("Stock: %.2f unidades\n", stockproducto[i]);
                        printf("-----------------------------------\n");
                    }
                } else {
                    printf("No hay productos registrados.\n");
                }
                break;

		            case 3:
                printf("Buscar por:\n");
                printf("1. ID\n");
                printf("2. Nombre\n");
                printf("3. Marca\n");
                scanf("%i", &opcion);
                encontrado = false;

                switch (opcion) {
                    case 1:
                        printf("Ingrese ID a buscar:\n");
                        scanf("%d", &idbuscar);
                        for (i = 0; i < cantidadproductos; i++) {
                            if (idproducto[i] == idbuscar) {
                                printf("Producto encontrado:\n");
                                printf("ID: %d | Nombre: %s | Marca: %s | Precio: $%.2f | Stock: %.2f\n",
                                       idproducto[i], nombreproducto[i], marcaproducto[i],
                                       precioproducto[i], stockproducto[i]);
                                encontrado = true;
                            }
                        }
                        break;

                    case 2:
                        printf("Ingrese nombre a buscar:\n");
                        scanf("%s", nombrebuscar);
                        for (i = 0; i < cantidadproductos; i++) {
                            if (strcmp(nombreproducto[i], nombrebuscar) == 0) {
                                printf("Producto encontrado:\n");
                                printf("ID: %d | Nombre: %s | Marca: %s | Precio: $%.2f | Stock: %.2f\n",
                                       idproducto[i], nombreproducto[i], marcaproducto[i],
                                       precioproducto[i], stockproducto[i]);
                                encontrado = true;
                            }
                        }
                        break;

                    case 3:
                        printf("Ingrese marca a buscar:\n");
                        scanf("%s", marcabuscar);
                        for (i = 0; i < cantidadproductos; i++) {
                            if (strcmp(marcaproducto[i], marcabuscar) == 0) {
                                printf("Producto encontrado:\n");
                                printf("ID: %d | Nombre: %s | Marca: %s | Precio: $%.2f | Stock: %.2f\n",
                                       idproducto[i], nombreproducto[i], marcaproducto[i],
                                       precioproducto[i], stockproducto[i]);
                                encontrado = true;
                            }
                        }
                        break;

                    default:
                        printf("Opcion de búsqueda no válida.\n");
                }

                if (!encontrado) {
                    printf("Producto no encontrado.\n");
                }
                break;
		case 4:
                if (cantidadproductos > 0) {
                    printf("Ingrese ID del producto a eliminar:\n");
                    scanf("%d", &idbuscar);
                    encontrado = false;

                    for (i = 0; i < cantidadproductos; i++) {
                        if (idproducto[i] == idbuscar) {
                            printf("Esta seguro de eliminar este producto? (S/N)\n");
                            printf("ID: %d | Nombre: %s | Marca: %s | Precio: $%.2f | Stock: %.2f\n",
                                   idproducto[i], nombreproducto[i], marcaproducto[i],
                                   precioproducto[i], stockproducto[i]);
                            scanf("%s", confirmacion);

                            if (strcmp(confirmacion, "S") == 0 || strcmp(confirmacion, "s") == 0) {
                                for (j = i; j < cantidadproductos - 1; j++) {
                                    idproducto[j] = idproducto[j + 1];
                                    strcpy(nombreproducto[j], nombreproducto[j + 1]);
                                    strcpy(marcaproducto[j], marcaproducto[j + 1]);
                                    precioproducto[j] = precioproducto[j + 1];
                                    stockproducto[j] = stockproducto[j + 1];
                                }
                                cantidadproductos--;
                                printf("Producto eliminado.\n");
                            } else {
                                printf("Operación cancelada.\n");
                            }
                            encontrado = true;
                            break;
                        }
                    }

                    if (!encontrado) {
                        printf("No se encontro producto con ID %d\n", idbuscar);
                    }
                } else {
                    printf("No hay productos para eliminar.\n");
                }
                break;
		case 5:
                if (cantidadproductos > 0) {
                    printf("Ingrese ID del producto a editar:\n");
                    scanf("%d", &idbuscar);
                    encontrado = false;

                    for (i = 0; i < cantidadproductos; i++) {
                        if (idproducto[i] == idbuscar) {
                            printf("Editando producto:\n");

                            printf("Nombre actual: %s | Ingrese nuevo nombre:\n", nombreproducto[i]);
                            scanf("%s", nombreproducto[i]);

                            printf("Marca actual: %s | Ingrese nueva marca:\n", marcaproducto[i]);
                            scanf("%s", marcaproducto[i]);

                            printf("Precio actual: $%.2f | Ingrese nuevo precio:\n", precioproducto[i]);
                            scanf("%f", &precioproducto[i]);

                            printf("Stock actual: %.2f | Ingrese nuevo stock:\n", stockproducto[i]);
                            scanf("%f", &stockproducto[i]);

                            printf("Producto actualizado correctamente.\n");
                            encontrado = true;
                            break;
                        }
                    }

                    if (!encontrado) {
                        printf("No se encontro producto con ID %d\n", idbuscar);
                    }
                } else {
                    printf("No hay productos para editar.\n");
                }
                break;
		            case 6:
                if (cantidadproductos > 0) {
                    printf("Ingrese ID del producto vendido:\n");
                    scanf("%d", &idbuscar);
                    encontrado = false;

                    for (i = 0; i < cantidadproductos; i++) {
                        if (idproducto[i] == idbuscar) {
                            printf("Producto: %s | Stock disponible: %.2f\n", nombreproducto[i], stockproducto[i]);
                            printf("Ingrese cantidad vendida:\n");
                            scanf("%d", &cantidadvendida);

                            if (cantidadvendida <= stockproducto[i]) {
                                idventa[cantidadventas] = cantidadventas + 1;
                                idproductoventa[cantidadventas] = idproducto[i];
                                cantidadventa[cantidadventas] = cantidadvendida;
                                strcpy(fechaventa[cantidadventas], "2025-07-23");  // Fecha simulada
                                stockproducto[i] -= cantidadvendida;
                                cantidadventas++;
                                printf("Venta registrada correctamente.\n");
                            } else {
                                printf("Error: Stock insuficiente para la venta.\n");
                            }
                            encontrado = true;
                            break;
                        }
                    }

                    if (!encontrado) {
                        printf("No se encontro producto con ID %d\n", idbuscar);
                    }
                } else {
                    printf("No hay productos para realizar ventas.\n");
                }
                break;
		case 7:
                if (cantidadventas > 0) {
                    printf("----- VENTAS REGISTRADAS -----\n");
                    for (i = 0; i < cantidadventas; i++) {
                        printf("Venta #%d | Producto ID: %d | Cantidad: %d | Fecha: %s\n",
                               idventa[i], idproductoventa[i], cantidadventa[i], fechaventa[i]);
                    }
                } else {
                    printf("No hay ventas registradas.\n");
                }
                break;
		            case 8:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opcion no válida.\n");
        }
    } while (opcion != 8);

    return 0;
}
