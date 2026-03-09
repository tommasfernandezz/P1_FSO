#include "sala.h"
#include <stdio.h>
#include <stdlib.h>

static int *asientos = NULL;
static int capacidad_actual = -1;
static int ocupados = 0;

int crea_sala(int capacidad) {
  if (asientos != NULL || capacidad <= 0) {
    return -1;
  }
  asientos = (int*) malloc(capacidad*sizeof(int));
  
  if (asientos == NULL) {
    return -1;
  }

  for (int i=0; i < capacidad; i++) {
    asientos[i]=0;
  }

  capacidad_actual = capacidad;
  ocupados = 0;
  return capacidad_actual;
}

int elimina_sala() {
  if (asientos == NULL) return -1;

  free(asientos);

  asientos = NULL;
  capacidad_actual = -1;
  ocupados = 0;
  return 0;
}

int reserva_asiento(int id_persona) {
  if (asientos == NULL || id_persona <= 0) return -1;

  if (ocupados >= capacidad_actual) return -1;

  for (int i = 0; i < capacidad_actual; i++) {
    if (asientos[i] == 0) {
      asientos[i] = id_persona;
      ocupados++;
      return i +1;
    }
  }
  return -1;
}

int asientos_ocupados() {
    if (asientos == NULL) return -1;
    return ocupados;
}

int asientos_libres() {
    if (asientos == NULL) return -1;
    return capacidad_actual - ocupados;

}

int estado_asiento(int id_asiento) {
    if (asientos == NULL) return -1;
    
    if (id_asiento <= 0 || id_asiento > capacidad_actual) return -1;

    return asientos[id_asiento - 1];
}

int libera_asiento(int id_asiento) {
    if (asientos == NULL || id_asiento <= 0 || id_asiento > capacidad_actual) return -1;

    if (asientos[id_asiento - 1] == 0) return -1;

    int id_persona = asientos[id_asiento - 1];
    asientos[id_asiento - 1] = 0;
    ocupados--;

    return id_persona;
}

int capacidad_sala() {
    if (asientos == NULL) return -1;
    return capacidad_actual;
}
