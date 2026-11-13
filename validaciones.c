#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "validaciones.h"

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
//idsjdjijfdsfjs