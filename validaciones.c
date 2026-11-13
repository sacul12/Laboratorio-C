#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "validaciones.h"
#include "artemis.h"

/* Interfaz de texto: solo printf y un ciclo for. */
void mostrarTitulo(char titulo[])
{
    printf("\n+--------------------------------------------------+\n");
    printf("| %-48s |\n", titulo);
    printf("+--------------------------------------------------+\n");
}

void mostrarProgreso(int realizados, int total)
{
    int i;
    printf("Orbita: [");
    for (i = 0; i < total; i++) {
        if (i < realizados) printf("#");
        else printf(".");
    }
    printf("] %d/%d turnos\n", realizados, total);
}

/* Doce lugares del dibujo: uno por cada turno de 30 grados. */
void mostrarOrbita(int turno, double altura, double velocidad,
                   double tiempo, double periodo)
{
    char posicion[TURNOS];
    int i;

    for (i = 0; i < TURNOS; i++) {
        if (i < turno) posicion[i] = '*';
        else posicion[i] = '.';
    }
    /* El resto permite volver al lugar inicial al completar la vuelta. */
    posicion[turno % TURNOS] = 'O';

    mostrarTitulo("CONTROL DE MISION - ORION");
    printf("\n                       %c\n", posicion[3]);
    printf("             %c                   %c\n", posicion[4], posicion[2]);
    printf("       %c                               %c\n", posicion[5], posicion[1]);
    printf("                  .----------.\n");
    printf("    %c            (   TIERRA   )            %c\n", posicion[6], posicion[0]);
    printf("                  '----------'\n");
    printf("       %c                               %c\n", posicion[7], posicion[11]);
    printf("             %c                   %c\n", posicion[8], posicion[10]);
    printf("                       %c\n\n", posicion[9]);
    printf(" O = Orion   * = recorrido   . = pendiente\n");
    printf(" Vista esquematica, sin escala. Giro antihorario.\n");
    printf("----------------------------------------------------\n");
    printf(" Turno: %2d / %d          Angulo: %3d grados\n", turno, TURNOS, turno * 30);
    printf(" Altura: %.2f km     Velocidad: %.2f m/s\n", altura, velocidad);
    printf(" Tiempo: %.2f s      Restante: %.2f s\n", tiempo, periodo - tiempo);
    printf("\n ");
    mostrarProgreso(turno, TURNOS);
    printf(" Avance: %.0f %%\n", 100.0 * turno / TURNOS);
    printf("----------------------------------------------------\n");
    if (turno == TURNOS) printf(" VUELTA COMPLETA: Orion regreso al punto inicial.\n");
    else printf(" [S] Avanzar 30 grados   [N] Terminar y ver reporte\n");
}

/* Lee hasta 63 caracteres. Si sobran, descarta la linea y vuelve a pedirla. */
static int leerLinea(char mensaje[], char texto[])
{
    int c;
    while (1) {
        printf("%s", mensaje);
        fflush(stdout);
        if (fgets(texto, 64, stdin) == NULL) return 0;
        if (strchr(texto, '\n') != NULL) return 1;
        c = getchar();
        if (c == '\n' || c == EOF) return 1;
        while (c != '\n' && c != EOF) c = getchar();
        printf("Entrada demasiado larga.\n");
    }
}

int leerNumero(char mensaje[], double minimo, double maximo, double *numero)
{
    char texto[64], extra;
    double valor;
    int i, valido;
    while (leerLinea(mensaje, texto)) {
        valido = 1;
        for (i = 0; texto[i] != '\0'; i++) {
            if (texto[i] == ',') texto[i] = '.';
            if (strchr("0123456789.+- \t\r\n", texto[i]) == NULL) valido = 0;
        }
        if (valido && sscanf(texto, "%lf %c", &valor, &extra) == 1) {
            if (valor >= minimo && valor <= maximo) {
                *numero = valor;
                return 1;
            }
        }
        printf("Ingrese un numero entre %.2f y %.2f, sin separador de miles.\n",
               minimo, maximo);
    }
    return 0;
}

int leerOpcion(void)
{
    double numero;
    while (leerNumero("Opcion: ", 0, 5, &numero)) {
        if (numero == (int)numero) return (int)numero;
        printf("La opcion debe ser entera.\n");
    }
    return -1;
}

int leerRespuesta(char *respuesta)
{
    char texto[64], letra, extra;
    while (leerLinea("Avanzar un turno (S/N): ", texto)) {
        if (sscanf(texto, " %c %c", &letra, &extra) == 1 &&
            strchr("sSnN", letra) != NULL) {
            *respuesta = letra;
            return 1;
        }
        printf("Ingrese solamente S o N.\n");
    }
    return 0;
}
