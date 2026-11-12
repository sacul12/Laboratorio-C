#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"
#include <math.h>

/* La altura se ingresa en km y el radio se calcula en metros. */
static double calcularRadio(double altura)
{
    double radio;
    radio = RADIO_TIERRA + altura * 1000;
    printf("r = %.0f + %.2f * 1000 = %.4f m\n", RADIO_TIERRA, altura, radio);
    return radio;
}

void calcularVelocidad(void)
{
    double altura, masa, radio, velocidad, fuerza;
    if (!leerNumero("Altura (100 a 2000 km): ", 100, 2000, &altura)) return;
    radio = calcularRadio(altura);
    if (!leerNumero("Masa de Orion (1 a 100000 kg): ", 1, 100000, &masa)) return;
    velocidad = sqrt(G * MASA_TIERRA / radio);
    fuerza = G * MASA_TIERRA * masa / (radio * radio);
    printf("La gravedad apunta al centro y actua como fuerza centripeta.\n");
    printf("Fg = G*M*m/r^2; Fc = m*v^2/r\n");
    printf("Igualando: G*M*m/r^2 = m*v^2/r\n");
    printf("Cancelamos m y despejamos: v = raiz(G*M/r)\n");
    printf("v = raiz(%.3e * %.3e / %.2f) = %.2f m/s\n",
           G, MASA_TIERRA, radio, velocidad);
    printf("Fg = Fc = %.3e * %.3e * %.2f / %.2f^2 = %.2f N\n",
           G, MASA_TIERRA, masa, radio, fuerza);
}

void calcularPeriodo(void)
{
    double altura, radio, velocidad, periodo;
    if (!leerNumero("Altura (100 a 2000 km): ", 100, 2000, &altura)) return;
    radio = calcularRadio(altura);
    velocidad = sqrt(G * MASA_TIERRA / radio);
    periodo = 2 * PI * radio / velocidad;
    printf("v = raiz(G*M/r) = %.2f m/s\n", velocidad);
    printf("T = 2*PI*r/v = 2*%.6f*%.2f/%.2f = %.2f s\n",
           PI, radio, velocidad, periodo);
    printf("En minutos: %.2f / 60 = %.2f min\n", periodo, periodo / 60);
}
