#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "../tdas/map.h"
#include "../tdas/list.h"
#include "../base/estructura.h"
extern Jugador *jugador;

// Cargar laberinto desde CSV
Map *cargar_laberinto(const char *archivo_csv, int *id_inicio);

// Inicializar jugador
Jugador *crear_jugador(int tiempo, int id_inicio);

// Mostrar estado actual del jugador
void mostrar_estado(Jugador *jugador, Escenario *escenario);

// Recoger ítems del escenario actual
void recoger_items(Jugador *jugador, Escenario *escenario);

// Descartar ítems del inventario del jugador
void descartar_items(Jugador *jugador);

// Mover jugador en una dirección (0=arriba, 1=abajo, 2=izquierda, 3=derecha)
int avanzar(Jugador *jugador, Map *grafo, int direccion);

// Reiniciar jugador
void reiniciar_jugador(Jugador *jugador, int tiempo, int id_inicio);

// Liberar memoria del jugador
void destruir_jugador(Jugador *jugador);

#endif
