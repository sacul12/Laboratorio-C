#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

int main(void)
{
    int opcion = 1;
    printf("CASI INGE - ORBITA DE ORION\n");
    while (opcion > 0) {
        printf("\n1. Fuerza y velocidad orbital\n");
        printf("2. Periodo orbital\n");
        printf("3. Aceleracion centripeta\n");
        printf("4. Pulso lateral\n");
        printf("5. Simular una vuelta\n");
        printf("0. Salir\n");
        opcion = leerOpcion();
        switch (opcion) {
            case 1: calcularVelocidad(); break;
            case 2: calcularPeriodo(); break;
            case 3: calcularAceleracion(); break;
            case 4: calcularPulso(); break;
            case 5: simularVuelta(); break;
        }
    }
    printf("Fin del programa.\n");
    return 0;
}
