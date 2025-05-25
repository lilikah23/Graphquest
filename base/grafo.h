#ifndef GRAFO_H
#define GRAFO_H

#include "../tdas/map.h"
#include "../tdas/list.h"
#include "../base/estructura.h"

Map *crear_grafo();

void agregar_escenario(Map *grafo, Escenario *esc);

Escenario *obtener_escenario(Map *grafo, int id);

void destruir_grafo(Map *grafo);

#endif
