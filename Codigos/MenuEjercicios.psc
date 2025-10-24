Algoritmo MenuEjercicios
	definir menu, valorEj  como Entero
	Definir nota Como Real
	Escribir "Menu Ejercicios"
	Escribir "1. Multiplos de 3 y 5"
	Escribir "2. Mensaje Merito"
	Escribir "3. Par / Impar"
	Escribir "Seleccione el ejercicio a ejecutar"
	Leer menu
	Segun menu Hacer
		1: 
			Escribir "1. Multiplos de 3 y 5"
			Escribir "Leer ek numero a consultar"
			Leer valorEj
			Si (valorEj %3 == 0) y (valorEj mod 5 == 0) Entonces
				Escribir "El numero(", valorEj, ") es multiplo de 3 y 5"
			FinSi
		2: Escribir "2. Mensaje Merito"
			Escribir "Ingresa la nota o la calificacion obtenida"
			Leer nota
			si nota >= 90 Entonces
				Escribir nota, "  es una calificación de sobresaliente"
			FinSi
		3: Escribir "3. Par / Impar"
			Escribir "Ingresa el valor a consultar"
			Leer valorEj
			si valorEj % 2 == 0 Entonces
				Escribir "El numero(", valorEj, ") es PAR"
			SiNo
				
				Escribir "El numero(", valorEj, ") es Impar"
				
			FinSi
		De Otro Modo:
			Escribir "No disponible"
	FinSegun
FinAlgoritmo
