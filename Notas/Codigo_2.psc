Caso 6:
                Escribir "Ingrese ID del producto vendido:"
                Leer idBuscar
                pos <- 0
                
                Para i <- 1 Hasta totalProductos - 1 Con Paso 1
                    Si listaID[i] = idBuscar Entonces
                        pos <- i
                    FinSi
                FinPara
                
                Si pos > 0 Entonces
                    Escribir "Ingrese cantidad vendida:"
                    Leer cantidadVendida
                    
                    Si cantidadVendida <= listaStock[pos] Entonces
                        listaStock[pos] <- listaStock[pos] - cantidadVendida
                        listaVendida[pos] <- listaVendida[pos] + cantidadVendida
                        Escribir "Venta registrada."
                    Sino
                        Escribir "Stock insuficiente."
                    FinSi
                Sino
                    Escribir "Producto no encontrado."
                FinSi
                
            Caso 7:
                Escribir "Ventas del día:"
                Para i <- 1 Hasta totalProductos - 1 Con Paso 1
                    Si listaVendida[i] > 0 Entonces
                        Escribir listaProducto[i], ": ", listaVendida[i], " unidades vendidas."
                    FinSi
                FinPara
                
            Caso 8:
                Escribir "Saliendo del sistema..."
                
            De Otro Modo:
                Escribir "Opción inválida"
        FinSegun
        
    Hasta Que opcion = 8
FinAlgoritmo
