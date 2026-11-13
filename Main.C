#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

int main(void)
{
    int opcion = 1;
    mostrarTitulo("CASI INGE - ORBITA DE ORION");
    printf("Escenario 2: orbita terrestre baja\n");
    while (opcion > 0) {
        mostrarTitulo("MENU PRINCIPAL");
        printf("| %-48s |\n", "1. Fuerza y velocidad orbital");
        printf("| %-48s |\n", "2. Periodo orbital");
        printf("| %-48s |\n", "3. Aceleracion centripeta");
        printf("| %-48s |\n", "4. Pulso lateral");
        printf("| %-48s |\n", "5. Simular una vuelta");
        printf("| %-48s |\n", "0. Salir");
        printf("+--------------------------------------------------+\n");
        opcion = leerOpcion();
        switch (opcion) {
            case 1: calcularVelocidad(); break;
            case 2: calcularPeriodo(); break;
            case 3: calcularAceleracion(); break;
            case 4: calcularPulso(); break;
            case 5: simularVuelta(); break;
        }
    }
    mostrarTitulo("Fin del programa.");
    return 0;
}
