/* Este codigo ha sido generado por el modulo psexport 20230904-w32 de PSeInt.
Es posible que el codigo generado no sea completamente correcto. Si encuentra
errores por favor reportelos en el foro (http://pseint.sourceforge.net). */

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

/* En C no hay variables para guardar cadenas de texto, sino que debe construirse
   un arreglo de caracteres (tipo char). El tamaño del arreglo determina la longitud
   máxima que puede tener la cadena que guarda (tamaño-1, por el caracter de terminación).
   La constante MAX_STRLEN define el tamaño máximo que se utiliza en este programa para
   cualquier cadena. */
#define MAX_STRLEN 256

/* Para leer variables de texto se utiliza scanf, que lee solo una palabra. 
   Para leer una linea completa (es decir, incluyendo los espacios en blanco)
   se debe utilzar ges (ej, reemplazar scanf("%s",x) por gets(x)) pero 
   obliga a agregar un getchar() antes del gets si antes del mismo se leyó
   otra variable con scanf. */

int main() {
	int cantidadproductos;
	int cantidadvendida;
	int cantidadventa[100];
	int cantidadventas;
	char confirmacion[MAX_STRLEN];
	bool encontrado;
	char fechaventa[MAX_STRLEN][100];
	int i;
	int idbuscar;
	float idproducto[100];
	float idproductoventa[100];
	int idventa[100];
	int j;
	char marcabuscar[MAX_STRLEN];
	char marcaproducto[MAX_STRLEN][100];
	char nombrebuscar[MAX_STRLEN];
	char nombreproducto[MAX_STRLEN][100];
	int opcion;
	float precioproducto[100];
	float stockproducto[100];
	/* --- DECLARACIÓN DE VARIABLES --- */
	/* --- ARREGLOS PARA DATOS DE PRODUCTOS --- */
	/* --- ARREGLOS PARA VENTAS --- */
	/* Inicialización */
	cantidadproductos = 1;
	/* ¡Cambiado a 1! (PSeInt usa índices desde 1) */
	cantidadventas = 1;
	do {
		printf("\n");
		printf("----- MENÚ PRINCIPAL -----\n");
		printf("1. Agregar producto\n");
		printf("2. Mostrar productos\n");
		printf("3. Buscar producto\n");
		printf("4. Eliminar producto\n");
		printf("5. Editar producto\n");
		printf("6. Registrar venta\n");
		printf("7. Ver ventas del día\n");
		printf("8. Salir\n");
		printf("--------------------------\n");
		printf("Ingrese una opción:\n");
		scanf("%i", &opcion);
		switch (opcion) {
		case 1:
			if (cantidadproductos<=100) {
				/* Validación del ID (no vacío y numérico) */
				do {
					printf("Ingrese ID del producto (número entero):\n");
					scanf("%f", &idproducto[cantidadproductos-1]);
					if (idproducto[cantidadproductos-1]<=0) {
						printf("Error: El ID debe ser un número positivo.\n");
					}
				} while (idproducto[cantidadproductos-1]<=0);
				/* Repite hasta que sea válido */
				/* Validación del nombre (no vacío) */
				do {
					printf("Ingrese nombre del producto:\n");
					scanf("%s", nombreproducto[cantidadproductos-1]);
					if (strcmp(nombreproducto[cantidadproductos-1], "")==0) {
						printf("Error: El nombre no puede estar vacío.\n");
					}
				} while (strcmp(nombreproducto[cantidadproductos-1], "")==0);
				/* Validación de la marca (no vacío) */
				do {
					printf("Ingrese marca del producto:\n");
					scanf("%s", marcaproducto[cantidadproductos-1]);
					if (strcmp(marcaproducto[cantidadproductos-1], "")==0) {
						printf("Error: La marca no puede estar vacía.\n");
					}
				} while (strcmp(marcaproducto[cantidadproductos-1], "")==0);
				/* Validación del precio (numérico y positivo) */
				do {
					printf("Ingrese precio del producto (ej: 19.99):\n");
					scanf("%f", &precioproducto[cantidadproductos-1]);
					if (precioproducto[cantidadproductos-1]<=0) {
						printf("Error: El precio debe ser mayor a 0.\n");
					}
				} while (precioproducto[cantidadproductos-1]<=0);
				/* Validación del stock (entero positivo) */
				do {
					printf("Ingrese stock disponible (entero positivo):\n");
					scanf("%f", &stockproducto[cantidadproductos-1]);
					if (stockproducto[cantidadproductos-1]<0) {
						printf("Error: El stock no puede ser negativo.\n");
					}
				} while (stockproducto[cantidadproductos-1]<0);
				cantidadproductos = cantidadproductos+1;
				printf("¡Producto registrado con éxito!\n");
			} else {
				printf("No hay espacio para más productos.\n");
			}
			break;
		case 2:
			if (cantidadproductos>1) {
				/* Mostrar aunque solo haya 1 producto */
				printf("=== LISTA DE PRODUCTOS ===\n");
				for (i=1; i<=cantidadproductos; ++i) {
					/* Recorre todos los productos */
					printf("-----------------------------------\n");
					printf("ID: %f\n", idproducto[i-1]);
					printf("Nombre: %s\n", nombreproducto[i-1]);
					printf("Marca: %s\n", marcaproducto[i-1]);
					printf("Precio: $%f\n", precioproducto[i-1]);
					printf("Stock: %f unidades\n", stockproducto[i-1]);
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
			switch (opcion) {
			case 1:
				printf("Ingrese ID a buscar:\n");
				scanf("%i", &idbuscar);
				for (i=1; i<=cantidadproductos-1; ++i) {
					/* Desde 1 */
					if (idproducto[i-1]==idbuscar) {
						printf("Producto encontrado:\n");
						printf("ID: %f | Nombre: %s | Marca: %s | Precio: $%f | Stock: %f\n", idproducto[i-1], nombreproducto[i-1], marcaproducto[i-1], precioproducto[i-1], stockproducto[i-1]);
						encontrado = true;
					}
				}
				if (!encontrado) {
					printf("No se encontró producto con ID %i\n", idbuscar);
				}
				break;
			case 2:
				printf("Ingrese nombre a buscar:\n");
				scanf("%s", nombrebuscar);
				for (i=1; i<=cantidadproductos-1; ++i) {
					/* Desde 1 */
					if (strcmp(nombreproducto[i-1], nombrebuscar)==0) {
						printf("Producto encontrado:\n");
						printf("ID: %f | Nombre: %s | Marca: %s | Precio: $%f | Stock: %f\n", idproducto[i-1], nombreproducto[i-1], marcaproducto[i-1], precioproducto[i-1], stockproducto[i-1]);
						encontrado = true;
					}
				}
				if (!encontrado) {
					printf("No se encontró producto con nombre: %s\n", nombrebuscar);
				}
				break;
			case 3:
				printf("Ingrese marca a buscar:\n");
				scanf("%s", marcabuscar);
				for (i=1; i<=cantidadproductos-1; ++i) {
					/* Desde 1 */
					if (strcmp(marcaproducto[i-1], marcabuscar)==0) {
						printf("Producto encontrado:\n");
						printf("ID: %f | Nombre: %s | Marca: %s | Precio: $%f | Stock: %f\n", idproducto[i-1], nombreproducto[i-1], marcaproducto[i-1], precioproducto[i-1], stockproducto[i-1]);
						encontrado = true;
					}
				}
				if (!encontrado) {
					printf("No se encontró producto de marca: %s\n", marcabuscar);
				}
				break;
			default:
				printf("Opción de búsqueda no válida.\n");
			}
			break;
		case 4:
			/* --- ELIMINAR PRODUCTO --- */
			if (cantidadproductos>0) {
				printf("Ingrese ID del producto a eliminar:\n");
				scanf("%i", &idbuscar);
				encontrado = false;
				i = 1;
				/* Inicializamos manualmente */
				while (i<=cantidadproductos && !encontrado) {
					/* Usamos MIENTRAS en lugar de PARA */
					if (idproducto[i-1]==idbuscar) {
						printf("¿Está seguro de eliminar este producto? (S/N)\n");
						printf("ID: %f | Nombre: %s | Marca: %s | Precio: $%f | Stock: %f\n", idproducto[i-1], nombreproducto[i-1], marcaproducto[i-1], precioproducto[i-1], stockproducto[i-1]);
						scanf("%s", confirmacion);
						if (strcmp(confirmacion, "S")==0 || strcmp(confirmacion, "s")==0) {
							if (cantidadproductos==1) {
								idproducto[i-1] = 0;
								/* Asegúrate de usar el tipo correcto (número o cadena) */
								nombreproducto[i-1] = "";
								marcaproducto[i-1] = "";
								precioproducto[i-1] = 0.0;
								stockproducto[i-1] = 0;
							} else {
								for (j=i; j<=cantidadproductos-1; ++j) {
									idproducto[j-1] = idproducto[j];
									nombreproducto[j-1] = nombreproducto[j];
									marcaproducto[j-1] = marcaproducto[j];
									precioproducto[j-1] = precioproducto[j];
									stockproducto[j-1] = stockproducto[j];
								}
							}
							cantidadproductos = cantidadproductos-1;
							printf("Producto eliminado.\n");
						} else {
							printf("Operación cancelada.\n");
						}
						encontrado = true;
						/* Al encontrarlo, saldrá del bucle */
					}
					i = i+1;
					/* Incrementamos manualmente */
				}
				if (!encontrado) {
					printf("No se encontró producto con ID %i\n", idbuscar);
				}
			} else {
				printf("No hay productos para eliminar.\n");
			}
			break;
		case 5:
			/* --- EDITAR PRODUCTO --- */
			if (cantidadproductos>0) {
				printf("Ingrese ID del producto a editar:\n");
				scanf("%i", &idbuscar);
				encontrado = false;
				for (i=1; i<=cantidadproductos-1; ++i) {
					if (idproducto[i-1]==idbuscar) {
						printf("Editando producto:\n");
						printf("Nombre actual: %s | Ingrese nuevo nombre:\n", nombreproducto[i-1]);
						scanf("%s", nombreproducto[i-1]);
						printf("Marca actual: %s | Ingrese nueva marca:\n", marcaproducto[i-1]);
						scanf("%s", marcaproducto[i-1]);
						printf("Precio actual: $%f | Ingrese nuevo precio:\n", precioproducto[i-1]);
						scanf("%f", &precioproducto[i-1]);
						printf("Stock actual: %f | Ingrese nuevo stock:\n", stockproducto[i-1]);
						scanf("%f", &stockproducto[i-1]);
						printf("Producto actualizado correctamente.\n");
						encontrado = true;
					}
				}
				if (!encontrado) {
					printf("No se encontró producto con ID %i\n", idbuscar);
				}
			} else {
				printf("No hay productos para editar.\n");
			}
			break;
		case 6:
			/* --- REGISTRAR VENTA --- */
			if (cantidadproductos>0) {
				printf("Ingrese ID del producto vendido:\n");
				scanf("%i", &idbuscar);
				encontrado = false;
				for (i=1; i<=cantidadproductos-1; ++i) {
					if (idproducto[i-1]==idbuscar) {
						printf("Producto: %s | Stock disponible: %f\n", nombreproducto[i-1], stockproducto[i-1]);
						printf("Ingrese cantidad vendida:\n");
						scanf("%i", &cantidadvendida);
						if (cantidadvendida<=stockproducto[i-1]) {
							idventa[cantidadventas-1] = cantidadventas;
							idproductoventa[cantidadventas-1] = idproducto[i-1];
							cantidadventa[cantidadventas-1] = cantidadvendida;
							fechaventa[cantidadventas-1] = "2025-07-23";
							/* Fecha simulada */
							stockproducto[i-1] = stockproducto[i-1]-cantidadvendida;
							cantidadventas = cantidadventas+1;
							printf("Venta registrada correctamente.\n");
						} else {
							printf("Error: Stock insuficiente para la venta.\n");
						}
						encontrado = true;
					}
				}
				if (!encontrado) {
					printf("No se encontró producto con ID %i\n", idbuscar);
				}
			} else {
				printf("No hay productos para realizar ventas.\n");
			}
			break;
		case 7:
			/* --- VER VENTAS DEL DÍA --- */
			if (cantidadventas>0) {
				printf("----- VENTAS REGISTRADAS -----\n");
				for (i=1; i<=cantidadventas-1; ++i) {
					printf("Venta #%i | Producto ID: %f | Cantidad: %i | Fecha: %s\n", idventa[i-1], idproductoventa[i-1], cantidadventa[i-1], fechaventa[i-1]);
				}
			} else {
				printf("No hay ventas registradas.\n");
			}
			break;
		case 8:
			printf("Saliendo del sistema...\n");
			break;
		default:
			printf("Opción no válida.\n");
		}
	} while (opcion!=8);
	return 0;
}

