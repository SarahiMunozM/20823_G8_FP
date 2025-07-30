Algoritmo SistemaGestionProductos
	Definir opcion, cantidadProductos, cantidadVentas, i, j, idBuscar, cantidadVendida Como Entero
	Definir nombreBuscar, marcaBuscar, confirmacion Como Cadena
	Definir encontrado Como Lógico
	Dimensionar idProducto(100)
	Dimensionar nombreProducto(100)
	Dimensionar marcaProducto(100)
	Dimensionar precioProducto(100)
	Dimensionar stockProducto(100)
	Dimensionar idVenta(100)
	Dimensionar idProductoVenta(100)
	Dimensionar cantidadVenta(100)
	Dimensionar fechaVenta(100)
	cantidadProductos <- 1
	cantidadVentas <- 1
	Repetir
		Escribir ''
		Escribir '----- MENÚ PRINCIPAL -----'
		Escribir '1. Agregar producto'
		Escribir '2. Mostrar productos'
		Escribir '3. Buscar producto'
		Escribir '4. Eliminar producto'
		Escribir '5. Editar producto'
		Escribir '6. Registrar venta'
		Escribir '7. Ver ventas del día'
		Escribir '8. Salir'
		Escribir '--------------------------'
		Escribir 'Ingrese una opción:'
		Leer opcion
		Según opcion Hacer
			1:
				Si cantidadProductos<=100 Entonces
					// Validación del ID (no vacío y numérico)
					Repetir
						Escribir 'Ingrese ID del producto (número entero):'
						Leer idProducto[cantidadProductos]
						Si idProducto[cantidadProductos]<=0 Entonces
							Escribir 'Error: El ID debe ser un número positivo.'
						FinSi
					Hasta Que idProducto[cantidadProductos]>0
					// Validación del nombre (no vacío)
					Repetir // Repite hasta que sea válido
						Escribir 'Ingrese nombre del producto:'
						Leer nombreProducto[cantidadProductos]
						Si nombreProducto[cantidadProductos]='' Entonces
							Escribir 'Error: El nombre no puede estar vacío.'
						FinSi
					Hasta Que nombreProducto[cantidadProductos]<>''
					// Validación de la marca (no vacío)
					Repetir
						Escribir 'Ingrese marca del producto:'
						Leer marcaProducto[cantidadProductos]
						Si marcaProducto[cantidadProductos]='' Entonces
							Escribir 'Error: La marca no puede estar vacía.'
						FinSi
					Hasta Que marcaProducto[cantidadProductos]<>''
					// Validación del precio (numérico y positivo)
					Repetir
						Escribir 'Ingrese precio del producto (ej: 19.99):'
						Leer precioProducto[cantidadProductos]
						Si precioProducto[cantidadProductos]<=0 Entonces
							Escribir 'Error: El precio debe ser mayor a 0.'
						FinSi
					Hasta Que precioProducto[cantidadProductos]>0
					// Validación del stock (entero positivo)
					Repetir
						Escribir 'Ingrese stock disponible (entero positivo):'
						Leer stockProducto[cantidadProductos]
						Si stockProducto[cantidadProductos]<0 Entonces
							Escribir 'Error: El stock no puede ser negativo.'
						FinSi
					Hasta Que stockProducto[cantidadProductos]>=0
					cantidadProductos <- cantidadProductos+1
					Escribir '¡Producto registrado con éxito!'
				SiNo
					Escribir 'No hay espacio para más productos.'
				FinSi
			2:
				Si cantidadProductos>1 Entonces
					Escribir '=== LISTA DE PRODUCTOS ===' // Mostrar aunque solo haya 1 producto
					Para i<-1 Hasta cantidadProductos Hacer
						Escribir '-----------------------------------' // Recorre todos los productos
						Escribir 'ID: ', idProducto[i]
						Escribir 'Nombre: ', nombreProducto[i]
						Escribir 'Marca: ', marcaProducto[i]
						Escribir 'Precio: $', precioProducto[i]
						Escribir 'Stock: ', stockProducto[i], ' unidades'
						Escribir '-----------------------------------'
					FinPara
				SiNo
					Escribir 'No hay productos registrados.'
				FinSi
			3:
				Escribir 'Buscar por:'
				Escribir '1. ID'
				Escribir '2. Nombre'
				Escribir '3. Marca'
				Leer opcion
				Según opcion Hacer
					1:
						Escribir 'Ingrese ID a buscar:'
						Leer idBuscar
						Para i<-1 Hasta cantidadProductos-1 Hacer
							Si idProducto[i]=idBuscar Entonces // Desde 1
								Escribir 'Producto encontrado:'
								Escribir 'ID: ', idProducto[i], ' | Nombre: ', nombreProducto[i], ' | Marca: ', marcaProducto[i], ' | Precio: $', precioProducto[i], ' | Stock: ', stockProducto[i]
								encontrado <- Verdadero
							FinSi
						FinPara
						Si  NO encontrado Entonces
							Escribir 'No se encontró producto con ID ', idBuscar
						FinSi
					2:
						Escribir 'Ingrese nombre a buscar:'
						Leer nombreBuscar
						Para i<-1 Hasta cantidadProductos-1 Hacer
							Si nombreProducto[i]=nombreBuscar Entonces // Desde 1
								Escribir 'Producto encontrado:'
								Escribir 'ID: ', idProducto[i], ' | Nombre: ', nombreProducto[i], ' | Marca: ', marcaProducto[i], ' | Precio: $', precioProducto[i], ' | Stock: ', stockProducto[i]
								encontrado <- Verdadero
							FinSi
						FinPara
						Si  NO encontrado Entonces
							Escribir 'No se encontró producto con nombre: ', nombreBuscar
						FinSi
					3:
						Escribir 'Ingrese marca a buscar:'
						Leer marcaBuscar
						Para i<-1 Hasta cantidadProductos-1 Hacer
							Si marcaProducto[i]=marcaBuscar Entonces // Desde 1
								Escribir 'Producto encontrado:'
								Escribir 'ID: ', idProducto[i], ' | Nombre: ', nombreProducto[i], ' | Marca: ', marcaProducto[i], ' | Precio: $', precioProducto[i], ' | Stock: ', stockProducto[i]
								encontrado <- Verdadero
							FinSi
						FinPara
						Si  NO encontrado Entonces
							Escribir 'No se encontró producto de marca: ', marcaBuscar
						FinSi
					De Otro Modo:
						Escribir 'Opción de búsqueda no válida.'
				FinSegún
			4:
				// --- ELIMINAR PRODUCTO ---
				Si cantidadProductos>0 Entonces
					Escribir 'Ingrese ID del producto a eliminar:'
					Leer idBuscar
					encontrado <- Falso
					i <- 1
					Mientras i<=cantidadProductos Y  NO encontrado Hacer // Inicializamos manualmente
						Si idProducto[i]=idBuscar Entonces // Usamos MIENTRAS en lugar de PARA
							Escribir '¿Está seguro de eliminar este producto? (S/N)'
							Escribir 'ID: ', idProducto[i], ' | Nombre: ', nombreProducto[i], ' | Marca: ', marcaProducto[i], ' | Precio: $', precioProducto[i], ' | Stock: ', stockProducto[i]
							Leer confirmacion
							Si confirmacion='S' O confirmacion='s' Entonces
								Si cantidadProductos=1 Entonces
									idProducto[i] <- 0
									nombreProducto[i] <- '' // Asegúrate de usar el tipo correcto (número o cadena)
									marcaProducto[i] <- ''
									precioProducto[i] <- 0.0
									stockProducto[i] <- 0
								SiNo
									Para j<-i Hasta cantidadProductos-1 Hacer
										idProducto[j] <- idProducto[j+1]
										nombreProducto[j] <- nombreProducto[j+1]
										marcaProducto[j] <- marcaProducto[j+1]
										precioProducto[j] <- precioProducto[j+1]
										stockProducto[j] <- stockProducto[j+1]
									FinPara
								FinSi
								cantidadProductos <- cantidadProductos-1
								Escribir 'Producto eliminado.'
							SiNo
								Escribir 'Operación cancelada.'
							FinSi
							encontrado <- Verdadero
						FinSi // Al encontrarlo, saldrá del bucle
						i <- i+1
					FinMientras // Incrementamos manualmente
					Si  NO encontrado Entonces
						Escribir 'No se encontró producto con ID ', idBuscar
					FinSi
				SiNo
					Escribir 'No hay productos para eliminar.'
				FinSi
			5:
				// --- EDITAR PRODUCTO ---
				Si cantidadProductos>0 Entonces
					Escribir 'Ingrese ID del producto a editar:'
					Leer idBuscar
					encontrado <- Falso
					Para i<-1 Hasta cantidadProductos-1 Hacer
						Si idProducto[i]=idBuscar Entonces
							Escribir 'Editando producto:'
							Escribir 'Nombre actual: ', nombreProducto[i], ' | Ingrese nuevo nombre:'
							Leer nombreProducto[i]
							Escribir 'Marca actual: ', marcaProducto[i], ' | Ingrese nueva marca:'
							Leer marcaProducto[i]
							Escribir 'Precio actual: $', precioProducto[i], ' | Ingrese nuevo precio:'
							Leer precioProducto[i]
							Escribir 'Stock actual: ', stockProducto[i], ' | Ingrese nuevo stock:'
							Leer stockProducto[i]
							Escribir 'Producto actualizado correctamente.'
							encontrado <- Verdadero
						FinSi
					FinPara
					Si  NO encontrado Entonces
						Escribir 'No se encontró producto con ID ', idBuscar
					FinSi
				SiNo
					Escribir 'No hay productos para editar.'
				FinSi
			6:
				// --- REGISTRAR VENTA ---
				Si cantidadProductos>0 Entonces
					Escribir 'Ingrese ID del producto vendido:'
					Leer idBuscar
					encontrado <- Falso
					Para i<-1 Hasta cantidadProductos-1 Hacer
						Si idProducto[i]=idBuscar Entonces
							Escribir 'Producto: ', nombreProducto[i], ' | Stock disponible: ', stockProducto[i]
							Escribir 'Ingrese cantidad vendida:'
							Leer cantidadVendida
							Si cantidadVendida<=stockProducto[i] Entonces
								idVenta[cantidadVentas] <- cantidadVentas
								idProductoVenta[cantidadVentas] <- idProducto[i]
								cantidadVenta[cantidadVentas] <- cantidadVendida
								fechaVenta[cantidadVentas] <- '2025-07-23'
								stockProducto[i] <- stockProducto[i]-cantidadVendida // Fecha simulada
								cantidadVentas <- cantidadVentas+1
								Escribir 'Venta registrada correctamente.'
							SiNo
								Escribir 'Error: Stock insuficiente para la venta.'
							FinSi
							encontrado <- Verdadero
						FinSi
					FinPara
					Si  NO encontrado Entonces
						Escribir 'No se encontró producto con ID ', idBuscar
					FinSi
				SiNo
					Escribir 'No hay productos para realizar ventas.'
				FinSi
			7:
				// --- VER VENTAS DEL DÍA ---
				Si cantidadVentas>0 Entonces
					Escribir '----- VENTAS REGISTRADAS -----'
					Para i<-1 Hasta cantidadVentas-1 Hacer
						Escribir 'Venta #', idVenta[i], ' | Producto ID: ', idProductoVenta[i], ' | Cantidad: ', cantidadVenta[i], ' | Fecha: ', fechaVenta[i]
					FinPara
				SiNo
					Escribir 'No hay ventas registradas.'
				FinSi
			8:
				Escribir 'Saliendo del sistema...'
			De Otro Modo:
				Escribir 'Opción no válida.'
		FinSegún
	Hasta Que opcion=8
FinAlgoritmo
