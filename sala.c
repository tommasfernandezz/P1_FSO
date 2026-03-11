#include "sala.h"
#include <stdio.h>
#include <stdlib.h>

/* Variables globales que guardan el estado de la sala */

static int *asientos = NULL;      // Array dinámico que representa los asientos
static int capacidad_actual = -1; // Capacidad total de la sala
static int ocupados = 0;          // Número de asientos ocupados


/* Crea una sala con un número de asientos */
int crea_sala(int capacidad) {

  // Error si ya existe una sala || la capacidad es menor o igual a 0
  if (asientos != NULL || capacidad <= 0) {
    return -1;
  }

  // Reserva memoria para los asientos
  asientos = (int*) malloc(capacidad*sizeof(int));
  
  // Error si no se pudo reservar memoria
  if (asientos == NULL) {
    return -1;
  }

  // Inicializa todos los asientos como libres (0)
  for (int i=0; i < capacidad; i++) {
    asientos[i]=0;
  }

  capacidad_actual = capacidad;
  ocupados = 0;

  return capacidad_actual;
}


/* Elimina la sala y libera la memoria */
int elimina_sala() {

  // Error si la sala no existe
  if (asientos == NULL) return -1;

  free(asientos); // Libera la memoria de los asientos

  asientos = NULL; // Reinicia el puntero
  capacidad_actual = -1;
  ocupados = 0;

  return 0;
}


/* Reserva el primer asiento libre */
int reserva_asiento(int id_persona) {

  // Error si la sala no existe || el id de la persona es inválido
  if (asientos == NULL || id_persona <= 0) return -1;

  // Error si la sala está llena
  if (ocupados >= capacidad_actual) return -1;

  // Busca el primer asiento libre
  for (int i = 0; i < capacidad_actual; i++) {

    if (asientos[i] == 0) { // Si el asiento está libre

      asientos[i] = id_persona; // Asigna la persona al asiento
      ocupados++; // Aumenta el número de ocupados

      return i +1; // Devuelve el número de asiento (empieza en 1)
    }
  }

  return -1;
}


/* Devuelve el número de asientos ocupados */
int asientos_ocupados() {

    // Error si la sala no existe
    if (asientos == NULL) return -1;

    return ocupados;
}


/* Devuelve el número de asientos libres */
int asientos_libres() {

    // Error si la sala no existe
    if (asientos == NULL) return -1;

    return capacidad_actual - ocupados;
}


/* Devuelve el estado de un asiento */
int estado_asiento(int id_asiento) {

    // Error si la sala no existe
    if (asientos == NULL) return -1;
    
    // Error si el número de asiento es inválido
    if (id_asiento <= 0 || id_asiento > capacidad_actual) return -1;

    return asientos[id_asiento - 1]; // Devuelve 0 si está libre o el id de la persona
}


/* Libera un asiento */
int libera_asiento(int id_asiento) {

    // Error si la sala no existe || el asiento no es válido
    if (asientos == NULL || id_asiento <= 0 || id_asiento > capacidad_actual) return -1;

    // Error si el asiento ya está libre
    if (asientos[id_asiento - 1] == 0) return -1;

    int id_persona = asientos[id_asiento - 1]; // Guarda la persona que estaba sentada

    asientos[id_asiento - 1] = 0; // Libera el asiento
    ocupados--; // Reduce el número de ocupados

    return id_persona;
}


/* Devuelve la capacidad total de la sala */
int capacidad_sala() {

    // Error si la sala no existe
    if (asientos == NULL) return -1;

    return capacidad_actual;
}
