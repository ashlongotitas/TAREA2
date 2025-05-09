#ifndef EXTRA_H
#define EXTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

char **leer_linea_csv(FILE *archivo, char separador);

List *split_string(const char *str, const char *delim);

// Función para limpiar la pantalla
void limpiarPantalla();

void presioneTeclaParaContinuar();

#endif
