# Casi Inge · Laboratorio de C

Escenario 2: inserción y estabilidad en órbita terrestre baja de Orion.

Integrantes: Lucas Beneventano, Matias Davila y Marcos Pezzelato. Comisión: Comision D.

## Abrir y ejecutar

En VS Code, abrir esta carpeta, la que contiene `main.c`. En Terminal > New Terminal ejecutar uno por vez:

```powershell
.\artemis.exe
```

## Archivos y punto 5.1

- `main.c`: únicamente `main`, menú e inicio del flujo.
- `artemis.h`: constantes, estructura `Orbita` y prototipos.
- `artemis.c`: fórmulas, cálculos, avance de la simulación y reporte.
- `validaciones.c` y `validaciones.h`: ingreso seguro de números, opciones enteras y caracteres S/N.

## Funcionamiento

La interfaz usa recuadros de texto para separar el menú y cada cálculo. La opción 5 muestra un dibujo de la Tierra y doce posiciones: `O` es Orion, `*` indica lugares recorridos y `.` los pendientes. Orion avanza en sentido antihorario y vuelve al inicio en el turno 12. El dibujo es esquemático, sin escala. Cada turno muestra altura, velocidad, ángulo, tiempo transcurrido y restante, porcentaje y una barra que se llena con `#`. Cada vista se imprime debajo de la anterior para conservar el historial.

La función `mostrarOrbita`, en el módulo de interfaz, usa un arreglo de caracteres, un ciclo `for`, condiciones y `printf`. La expresión `turno % TURNOS` permite volver a la posición cero al completar doce turnos. No requiere bibliotecas gráficas. El dibujo y la barra son mejoras opcionales de presentación; la consigna exige una interfaz clara por consola. Estas mejoras fueron solicitadas a Codex / ChatGPT como una interfaz sencilla por terminal y una presentación más linda de la simulación por turnos. Se comprobaron las 42 pruebas anteriores y las 13 vistas desde el inicio hasta completar una vuelta.

Las opciones 1 a 4 son cálculos independientes. Cada una pide datos y muestra la fórmula con los valores ingresados. La opción 5 inicia una simulación circular independiente: se ingresa la altura y se responde S para avanzar 30 grados o N para terminar. Doce turnos completan una vuelta. Al terminar aparece un reporte completo o parcial. La opción 0 cierra el programa.

La estructura `Orbita` tiene altura, velocidad y período. El arreglo `tiempos[12]` registra los turnos realizados; sólo se leen las posiciones que se llenaron. Los punteros aparecen en las funciones de lectura: `&altura` entrega la dirección de una variable y `*numero = valor` guarda el dato en esa dirección. Cada cálculo tiene su propia función y variables locales.

`fgets` limita las líneas a 63 caracteres. `strchr` comprueba sus caracteres y `sscanf` convierte los números y detecta texto sobrante. Se aceptan punto o coma decimal, sin separadores de miles ni exponentes. Se rechazan entradas vacías, letras, números fuera de rango y varios datos en una línea. El fin de entrada cierra el programa; durante una simulación se muestra el reporte parcial.

## Modelo y fórmulas

Se toman de la consigna G = 6,674 × 10^-11 N·m²/kg², masa terrestre M = 5,972 × 10^24 kg y radio terrestre R = 6371000 m. G es la constante gravitatoria, no una aceleración.

```text
r = R + altura_en_km * 1000
Fg = G*M*m/r²; Fc = m*v²/r
Fg = Fc => v = sqrt(G*M/r)
T = 2*PI*r/v
ac = G*M/r²
Desviación lateral aproximada = a*t²/2
Cambio de velocidad lateral = a*t
```

La gravedad proporciona la fuerza centrípeta: no son fuerzas que se suman. Los astronautas están en caída libre orbital. Se considera una Tierra esférica, sin atmósfera ni otros cuerpos. Los rangos educativos elegidos son: altura de 100 a 2000 km, masa de 1 a 100000 kg, aceleración lateral de 0 a 1 m/s² y duración de 0 a 10 s. No se calcula la duración de una órbita real con rozamiento, incluso en el extremo de 100 km.

El pulso usa una dirección lateral local fija, velocidad lateral inicial cero respecto de la trayectoria sin pulso y giro despreciable de los ejes durante el intervalo breve. `x ≈ v*t` e `y ≈ a*t²/2` describen una parábola local aproximada, no una órbita posterior parabólica. La desviación no es necesariamente un aumento de altura. La gravedad continúa actuando y la órbita posterior depende de la orientación espacial del empuje, que no está precisada. El ensayo del pulso no modifica la simulación circular independiente.


## Material e inteligencia artificial

Referencias: CursoC-I y CursoC-II en PDF y PPT; Herramientas; Intro a C de Marzal y Gracia; Introducción a la programación en C de Peña y Cela; Programación en C de Joyanes Aguilar y Zahonero Martínez; Programacion en C; Tipos y Estructuras de Datos; Trabajo Final Integrador C. Se aplican variables, condicionales, ciclos, funciones, arreglos, estructuras, punteros, cabeceras y biblioteca estándar.

Se utilizó OpenAI Codex / ChatGPT para analizar la consigna y el material, generar y simplificar una base, comprobar cálculos y entradas.
