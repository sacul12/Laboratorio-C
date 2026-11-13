#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Devuelve 1 si obtuvo un dato y 0 si termino la entrada. */
int leerNumero(char mensaje[], double minimo, double maximo, double *numero);
int leerRespuesta(char *respuesta);
int leerOpcion(void);
void mostrarTitulo(char titulo[]);
void mostrarProgreso(int realizados, int total);
void mostrarOrbita(int turno, double altura, double velocidad,
                   double tiempo, double periodo);

#endif
