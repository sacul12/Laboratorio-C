#include <stdio.h>
#include <math.h>
#include "Artemis.h"
#include "validaciones.h"

/* La altura se ingresa en km y el radio se calcula en metros. */
static double calcularRadio(double altura)
{
    double radio;
    radio = RADIO_TIERRA + altura * 1000;
    printf("r = %.0f + %.2f * 1000 = %.2f m\n", RADIO_TIERRA, altura, radio);
    return radio;
}

void calcularVelocidad(void)
{
    double altura, masa, radio, velocidad, fuerza;
    mostrarTitulo("1. FUERZA Y VELOCIDAD ORBITAL");
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
    mostrarTitulo("2. PERIODO ORBITAL");
    if (!leerNumero("Altura (100 a 2000 km): ", 100, 2000, &altura)) return;
    radio = calcularRadio(altura);
    velocidad = sqrt(G * MASA_TIERRA / radio);
    periodo = 2 * PI * radio / velocidad;
    printf("v = raiz(G*M/r) = %.2f m/s\n", velocidad);
    printf("T = 2*PI*r/v = 2*%.6f*%.2f/%.2f = %.2f s\n",
           PI, radio, velocidad, periodo);
    printf("En minutos: %.2f / 60 = %.2f min\n", periodo, periodo / 60);
}

void calcularAceleracion(void)
{
    double altura, radio, aceleracion;
    mostrarTitulo("3. ACELERACION CENTRIPETA");
    if (!leerNumero("Altura (100 a 2000 km): ", 100, 2000, &altura)) return;
    radio = calcularRadio(altura);
    aceleracion = G * MASA_TIERRA / (radio * radio);
    printf("ac = v^2/r = G*M/r^2\n");
    printf("ac = %.3e * %.3e / %.2f^2 = %.4f m/s2\n",
           G, MASA_TIERRA, radio, aceleracion);
    printf("Apunta al centro terrestre. Orion y los astronautas estan en caida libre.\n");
}

void calcularPulso(void)
{
    double aceleracion, tiempo, desviacion, cambioVelocidad;
    mostrarTitulo("4. PULSO LATERAL");
    if (!leerNumero("Aceleracion lateral (0 a 1 m/s2): ", 0, 1, &aceleracion)) return;
    if (!leerNumero("Duracion (0 a 10 s): ", 0, 10, &tiempo)) return;
    desviacion = aceleracion * tiempo * tiempo / 2;
    cambioVelocidad = aceleracion * tiempo;
    printf("Desviacion = a*t^2/2 = %.2f*%.2f^2/2 = %.2f m\n",
           aceleracion, tiempo, desviacion);
    printf("Cambio de velocidad = a*t = %.2f*%.2f = %.2f m/s\n",
           aceleracion, tiempo, cambioVelocidad);
    if (aceleracion == 0 || tiempo == 0) {
        printf("Pulso nulo: no se agrega desviacion.\n");
    } else {
        printf("La nave se aparta de la orbita original. Aproximacion local breve:\n");
        printf("direccion lateral fija, velocidad lateral inicial cero y giro despreciable.\n");
        printf("x aproximadamente v*t; y aproximadamente a*t^2/2: parabola local.\n");
        printf("La desviacion se mide respecto de la trayectoria sin pulso; no es\n");
        printf("necesariamente un cambio de altura. La gravedad sigue actuando.\n");
        printf("No se calcula la orbita posterior: depende de la orientacion del empuje.\n");
    }
}

void simularVuelta(void)
{
    Orbita nave;
    double radio, tiempos[TURNOS];
    int cantidad = 0, i;
    char respuesta = 's';
    mostrarTitulo("5. SIMULAR UNA VUELTA");
    if (!leerNumero("Altura de la simulacion (100 a 2000 km): ", 100, 2000, &nave.altura)) return;
    radio = calcularRadio(nave.altura);
    nave.velocidad = sqrt(G * MASA_TIERRA / radio);
    nave.periodo = 2 * PI * radio / nave.velocidad;
    printf("Modelo circular ideal, sin atmosfera ni otros cuerpos.\n");
    printf("Cada turno avanza 30 grados. Objetivo: completar 12 turnos.\n");
    mostrarOrbita(0, nave.altura, nave.velocidad, 0, nave.periodo);
    while (cantidad < TURNOS && (respuesta == 's' || respuesta == 'S')) {
        if (!leerRespuesta(&respuesta)) break;
        if (respuesta == 's' || respuesta == 'S') {
            tiempos[cantidad] = nave.periodo * (cantidad + 1) / TURNOS;
            printf("Turno %d: %.2f s, %d grados\n", cantidad + 1, tiempos[cantidad], (cantidad + 1) * 30);
            cantidad++;
            mostrarOrbita(cantidad, nave.altura, nave.velocidad,
                          tiempos[cantidad - 1], nave.periodo);
        }
    }
    mostrarTitulo("REPORTE DE LA VUELTA");
    printf("Altura: %.2f km; velocidad: %.2f m/s\n", nave.altura, nave.velocidad);
    printf("Periodo: %.2f s (%.2f min)\n", nave.periodo, nave.periodo / 60);
    printf("Turno     Tiempo (s)\n");
    for (i = 0; i < cantidad; i++) {
        printf("%5d %14.2f\n", i + 1, tiempos[i]);
    }
    printf("Progreso: %d de %d turnos, %.2f %%\n", cantidad, TURNOS, 100.0 * cantidad / TURNOS);
    if (cantidad == TURNOS) printf("MISION COMPLETADA.\n");
    else printf("Simulacion finalizada antes de completar la vuelta.\n");
}
