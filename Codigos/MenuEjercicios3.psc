Algoritmo MenuEjercicios
	definir menu, valorEj, anio como Entero
	Definir nota, temperatura, salario, bono Como Real
	Definir cargo como Cadena
	Escribir "Menu Ejercicios"
	Escribir "1. Multiplos de 3 y 5"
	Escribir "2. Mensaje Merito"
	Escribir "3. Par / Impar"
	Escribir "4. Año bisiesto"
	Escribir "5. Clasificar temperatura"
	Escribir "6. Bonificacion Empleado"
	Escribir "7. Calificacion Cualitativa"
	
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
		4:  Escribir "4. Año bisiesto"
			Escribir "Ingrese el año a consultar"
			Leer valorEj
			si (valorEj mod 4 == 0) y (valorEj % 100 == 0) o (valorEj mod 400	==	0) Entonces
				Escribir"El año(",valorEj, ")Es Bisiesto"
			SiNo
				Escribir"El año(",valorEj, ")no es Bisiesto"
			FinSi
		5:  Escribir "5. Clasificar temperatura"
			Escribir "Ingresar la temperatura en °C"
			Leer temperatura
			si  temperatura < 15 Entonces
				Escribir   ,temperatura, "°C Clima Frio"
			SiNo
				si temperatura < 30 Entonces
					Escribir temperatura, "°C Clima Templado"
				SiNo
					Escribir  temperatura, "°C Clima Caliente"
					
				FinSi
			FinSi
		6: Escribir "6. Bonificacion Empleado"
			Escribir "Ingrese el cargo (Gerente/Empleado)"
			Leer  cargo
			Escribir "Ingresar el salario"
			Leer salario
			Escribir "Ingresar los años de servicio"
			Leer anio
			Si cargo == "Gerente" Entonces
				si anio > 5 Entonces
					bono= salario * 0.20
					salario = salario + bono
				SiNo
					bono= salario * 0.10
					salario = salario + bono
				FinSi
			SiNo
				//Empleado
				si anio > 5  Entonces
					bono= salario * 0.07
					salario = salario + bono
				SiNo
					bono= salario * 0.03
					salario = salario + bono
				FinSi
				
			FinSi
			Escribir "Cargo:", cargo
			Escribir "Con el bono de  ", bono, "   el salario a recibir es   ", salario, "  dolares "
		7: Escribir "7. Calificacion Cualitativa"
			Escribir " Ingrese el promedio obtenido:"
			Leer nota
			Si nota < 70 Entonces
				Escribir "Calificacion obtenida   ", nota, ".   REPROBADO"
			SiNo
				Si nota >= 70 y nota < 90 Entonces // rango entre 71 y 89
					Escribir "Calificacion obtenida   ", nota, ".   APROBADO"
				SiNo
					Escribir "Calificacion obtenida   ", nota, ".   EXCELENTE"
				FinSi
			FinSi
		De Otro Modo:
			Escribir "No disponible"
	FinSegun
FinAlgoritmo
