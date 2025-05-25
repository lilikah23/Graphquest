#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include "../tdas/list.h"

//estructura de un item
// contiene el nombre, valor y peso del item
typedef struct {
    char nombre[50];
    int valor;
    int peso;
} Item;

//estructura de un escenario
// contiene el id, nombre, descripcion, lista de items, conexiones y si es final
typedef struct {
    int id;
    char nombre[50];
    char descripcion[300];
    List *items; // Lista de Item*
    int conexiones[4]; // 0: arriba, 1: abajo, 2: izquierda, 3: derecha
    int es_final;
} Escenario;

//estructura de un jugador
// contiene el tiempo restante, inventario, peso total, puntaje total y escenario actual
typedef struct {
    int tiempo_restante;
    List *inventario; // Lista de Item*
    int peso_total;
    int puntaje_total;
    int escenario_actual_id;
} Jugador;

#endif