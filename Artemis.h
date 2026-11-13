#ifndef ARTEMIS_H
#define ARTEMIS_H

#define G 6.674e-11
#define MASA_TIERRA 5.972e24
#define RADIO_TIERRA 6371000.0
#define PI 3.141592653589793
#define TURNOS 12

/* Esta estructura solo se usa en la simulacion de una vuelta. */
typedef struct {
    double altura;
    double velocidad;
    double periodo;
} Orbita;

void calcularVelocidad(void);
void calcularPeriodo(void);
void calcularAceleracion(void);
void calcularPulso(void);
void simularVuelta(void);

#endif
