Proceso SistemaGestionProductos
    // --- DECLARACIÓN DE VARIABLES ---
    Definir opcion, cantidadProductos, cantidadVentas, i, j, idBuscar, cantidadVendida Como Entero
    Definir nombreBuscar, marcaBuscar, confirmacion Como Caracter
    Definir encontrado Como Logico
	
    // --- ARREGLOS PARA DATOS DE PRODUCTOS ---
    Dimension idProducto[100]
    Dimension nombreProducto[100]
    Dimension marcaProducto[100]
    Dimension precioProducto[100]
    Dimension stockProducto[100]
	
    // --- ARREGLOS PARA VENTAS ---
    Dimension idVenta[100]
    Dimension idProductoVenta[100]
    Dimension cantidadVenta[100]
    Dimension fechaVenta[100]
	
    // Inicialización
    cantidadProductos <- 1  // ¡Cambiado a 1! (PSeInt usa índices desde 1)
    cantidadVentas <- 1
    
    Repetir
        Escribir "";
        Escribir "----- MENÚ PRINCIPAL -----";
        Escribir "1. Agregar producto";
        Escribir "2. Mostrar productos";
        Escribir "3. Buscar producto";
        Escribir "4. Eliminar producto";
        Escribir "5. Editar producto";
        Escribir "6. Registrar venta";
        Escribir "7. Ver ventas del día";
        Escribir "8. Salir";
        Escribir "--------------------------";
        Escribir "Ingrese una opción:";
        Leer opcion;
        
        Segun opcion Hacer
            1:
				Si cantidadProductos <= 100 Entonces
					// Validación del ID (no vacío y numérico)
					Repetir
						Escribir "Ingrese ID del producto (número entero):"
						Leer idProducto[cantidadProductos]
						Si idProducto[cantidadProductos] <= 0 Entonces
							Escribir "Error: El ID debe ser un número positivo."
						FinSi
					Hasta Que idProducto[cantidadProductos] > 0  // Repite hasta que sea válido
					
					// Validación del nombre (no vacío)
					Repetir
						Escribir "Ingrese nombre del producto:"
						Leer nombreProducto[cantidadProductos]
						Si nombreProducto[cantidadProductos] = "" Entonces
							Escribir "Error: El nombre no puede estar vacío."
						FinSi
					Hasta Que nombreProducto[cantidadProductos] <> ""
					
					// Validación de la marca (no vacío)
					Repetir
						Escribir "Ingrese marca del producto:"
						Leer marcaProducto[cantidadProductos]
						Si marcaProducto[cantidadProductos] = "" Entonces
							Escribir "Error: La marca no puede estar vacía."
						FinSi
					Hasta Que marcaProducto[cantidadProductos] <> ""
					
					// Validación del precio (numérico y positivo)
					Repetir
						Escribir "Ingrese precio del producto (ej: 19.99):"
						Leer precioProducto[cantidadProductos]
						Si precioProducto[cantidadProductos] <= 0 Entonces
							Escribir "Error: El precio debe ser mayor a 0."
						FinSi
					Hasta Que precioProducto[cantidadProductos] > 0
					
					// Validación del stock (entero positivo)
					Repetir
						Escribir "Ingrese stock disponible (entero positivo):"
						Leer stockProducto[cantidadProductos]
						Si stockProducto[cantidadProductos] < 0 Entonces
							Escribir "Error: El stock no puede ser negativo."
						FinSi
					Hasta Que stockProducto[cantidadProductos] >= 0
					
					cantidadProductos <- cantidadProductos + 1
					Escribir "¡Producto registrado con éxito!"
				Sino
					Escribir "No hay espacio para más productos."
				FinSi
                
            2:
                Si cantidadProductos > 1 Entonces  // Mostrar aunque solo haya 1 producto
					Escribir "=== LISTA DE PRODUCTOS ==="
					Para i <- 1 Hasta cantidadProductos Hacer  // Recorre todos los productos
						Escribir "-----------------------------------"
						Escribir "ID: ", idProducto[i]
						Escribir "Nombre: ", nombreProducto[i]
						Escribir "Marca: ", marcaProducto[i]
						Escribir "Precio: $", precioProducto[i]
						Escribir "Stock: ", stockProducto[i], " unidades"
						Escribir "-----------------------------------"
					FinPara
				Sino
					Escribir "No hay productos registrados."
				FinSi
                
            3:
                Escribir "Buscar por:";
                Escribir "1. ID";
                Escribir "2. Nombre";
                Escribir "3. Marca";
                Leer opcion;
                
                Segun opcion Hacer
                    1:
                        Escribir "Ingrese ID a buscar:"
                        Leer idBuscar
                        Para i <- 1 Hasta cantidadProductos - 1 Hacer  // Desde 1
                            Si idProducto[i] = idBuscar Entonces
                                Escribir "Producto encontrado:"
                                Escribir "ID: ", idProducto[i], " | Nombre: ", nombreProducto[i], " | Marca: ", marcaProducto[i], " | Precio: $", precioProducto[i], " | Stock: ", stockProducto[i]
                                encontrado <- Verdadero
                            FinSi
                        FinPara
                        Si No encontrado Entonces
                            Escribir "No se encontró producto con ID ", idBuscar
                        FinSi
						
                    2:
                        Escribir "Ingrese nombre a buscar:"
                        Leer nombreBuscar
                        Para i <- 1 Hasta cantidadProductos - 1 Hacer  // Desde 1
                            Si nombreProducto[i] = nombreBuscar Entonces
                                Escribir "Producto encontrado:"
                                Escribir "ID: ", idProducto[i], " | Nombre: ", nombreProducto[i], " | Marca: ", marcaProducto[i], " | Precio: $", precioProducto[i], " | Stock: ", stockProducto[i]
                                encontrado <- Verdadero
                            FinSi
                        FinPara
                        Si No encontrado Entonces
                            Escribir "No se encontró producto con nombre: ", nombreBuscar
                        FinSi
						
                    3:
                        Escribir "Ingrese marca a buscar:"
                        Leer marcaBuscar
                        Para i <- 1 Hasta cantidadProductos - 1 Hacer  // Desde 1
                            Si marcaProducto[i] = marcaBuscar Entonces
                                Escribir "Producto encontrado:"
                                Escribir "ID: ", idProducto[i], " | Nombre: ", nombreProducto[i], " | Marca: ", marcaProducto[i], " | Precio: $", precioProducto[i], " | Stock: ", stockProducto[i]
                                encontrado <- Verdadero
                            FinSi
                        FinPara
                        Si No encontrado Entonces
                            Escribir "No se encontró producto de marca: ", marcaBuscar
                        FinSi
						
                    De Otro Modo:
                        Escribir "Opción de búsqueda no válida."
                FinSegun
                
            4:
                // --- ELIMINAR PRODUCTO ---
				Si cantidadProductos > 0 Entonces
					Escribir "Ingrese ID del producto a eliminar:"
					Leer idBuscar
					encontrado <- Falso
					i <- 1  // Inicializamos manualmente
					Mientras i <= cantidadProductos Y No encontrado Hacer  // Usamos MIENTRAS en lugar de PARA
						Si idProducto[i] = idBuscar Entonces
							Escribir "¿Está seguro de eliminar este producto? (S/N)"
							Escribir "ID: ", idProducto[i], " | Nombre: ", nombreProducto[i], " | Marca: ", marcaProducto[i], " | Precio: $", precioProducto[i], " | Stock: ", stockProducto[i]
							Leer confirmacion
							Si confirmacion = "S" O confirmacion = "s" Entonces
								Si cantidadProductos = 1 Entonces
									idProducto[i] <- 0       // Asegúrate de usar el tipo correcto (número o cadena)
									nombreProducto[i] <- ""
									marcaProducto[i] <- ""
									precioProducto[i] <- 0.0
									stockProducto[i] <- 0
								Sino
									Para j <- i Hasta cantidadProductos - 1 Hacer
										idProducto[j] <- idProducto[j + 1]
										nombreProducto[j] <- nombreProducto[j + 1]
										marcaProducto[j] <- marcaProducto[j + 1]
										precioProducto[j] <- precioProducto[j + 1]
										stockProducto[j] <- stockProducto[j + 1]
									FinPara
								FinSi
								cantidadProductos <- cantidadProductos - 1
								Escribir "Producto eliminado."
							Sino
								Escribir "Operación cancelada."
							FinSi
							encontrado <- Verdadero  // Al encontrarlo, saldrá del bucle
						FinSi
						i <- i + 1  // Incrementamos manualmente
					FinMientras
					Si No encontrado Entonces
						Escribir "No se encontró producto con ID ", idBuscar
					FinSi
				Sino
					Escribir "No hay productos para eliminar."
				FinSi
            5:
                // --- EDITAR PRODUCTO ---
                Si cantidadProductos > 0 Entonces
                    Escribir "Ingrese ID del producto a editar:"
                    Leer idBuscar
                    encontrado <- Falso
                    Para i <- 1 Hasta cantidadProductos - 1 Hacer
                        Si idProducto[i] = idBuscar Entonces
                            Escribir "Editando producto:"
                            Escribir "Nombre actual: ", nombreProducto[i], " | Ingrese nuevo nombre:"
                            Leer nombreProducto[i]
                            Escribir "Marca actual: ", marcaProducto[i], " | Ingrese nueva marca:"
                            Leer marcaProducto[i]
                            Escribir "Precio actual: $", precioProducto[i], " | Ingrese nuevo precio:"
                            Leer precioProducto[i]
                            Escribir "Stock actual: ", stockProducto[i], " | Ingrese nuevo stock:"
                            Leer stockProducto[i]
                            Escribir "Producto actualizado correctamente."
                            encontrado <- Verdadero
                        FinSi
                    FinPara
                    Si No encontrado Entonces
                        Escribir "No se encontró producto con ID ", idBuscar
                    FinSi
                Sino
                    Escribir "No hay productos para editar."
                FinSi
				
            6:
                // --- REGISTRAR VENTA ---
                Si cantidadProductos > 0 Entonces
                    Escribir "Ingrese ID del producto vendido:"
                    Leer idBuscar
                    encontrado <- Falso
                    Para i <- 1 Hasta cantidadProductos - 1 Hacer
                        Si idProducto[i] = idBuscar Entonces
                            Escribir "Producto: ", nombreProducto[i], " | Stock disponible: ", stockProducto[i]
                            Escribir "Ingrese cantidad vendida:"
                            Leer cantidadVendida
                            Si cantidadVendida <= stockProducto[i] Entonces
                                idVenta[cantidadVentas] <- cantidadVentas
                                idProductoVenta[cantidadVentas] <- idProducto[i]
                                cantidadVenta[cantidadVentas] <- cantidadVendida
                                fechaVenta[cantidadVentas] <- "2025-07-23"  // Fecha simulada
                                stockProducto[i] <- stockProducto[i] - cantidadVendida
                                cantidadVentas <- cantidadVentas + 1
                                Escribir "Venta registrada correctamente."
                            Sino
                                Escribir "Error: Stock insuficiente para la venta."
                            FinSi
                            encontrado <- Verdadero
                        FinSi
                    FinPara
                    Si No encontrado Entonces
                        Escribir "No se encontró producto con ID ", idBuscar
                    FinSi
                Sino
                    Escribir "No hay productos para realizar ventas."
                FinSi
				
            7:
                // --- VER VENTAS DEL DÍA ---
                Si cantidadVentas > 0 Entonces
                    Escribir "----- VENTAS REGISTRADAS -----"
                    Para i <- 1 Hasta cantidadVentas - 1 Hacer
                        Escribir "Venta #", idVenta[i], " | Producto ID: ", idProductoVenta[i], " | Cantidad: ", cantidadVenta[i], " | Fecha: ", fechaVenta[i]
                    FinPara
                Sino
                    Escribir "No hay ventas registradas."
                FinSi
				
            8:
                Escribir "Saliendo del sistema..."
				
            De Otro Modo:
                Escribir "Opción no válida."
        FinSegun
		
    Hasta Que opcion = 8
FinAlgoritmo
