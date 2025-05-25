#include <stdio.h>
#include "../base/estructura.h"
#include "../base/funciones.h"
#include "../base/grafo.h"
#include "../tdas/list.h"
#include "../tdas/map.h"
#include "../tdas/extra.h"


//crea un grafo vacío
// y devuelve un puntero a él
Map* crear_grafo() {
    return map_create(int_cmp);
}

// Agrega un escenario al grafo usando su id como clave
void agregar_escenario(Map *grafo, Escenario *esc) {
    if (grafo == NULL || esc == NULL) {
        return;
    }
    map_insert(grafo, &esc->id, esc);
}

// Obtiene un escenario del grafo usando su id como clave
Escenario* obtener_escenario(Map *grafo, int id) {
    if (grafo == NULL) {
        return NULL;
    }
    MapPair *pair = map_get(grafo, &id);
    if (pair == NULL) return NULL;
    return (Escenario *)pair->value;
}

// Libera la memoria del grafo y de todos sus escenarios
void destruir_grafo(Map *grafo) {
    if (grafo == NULL) {
        return;
    }

    MapPair *pair = map_first(grafo);
    while (pair != NULL) {
        Escenario *esc = (Escenario *)pair->value;
        if (esc != NULL) {
            list_destroy(esc->items); // Usa list_destroy para liberar la lista de items
            free(esc); // Liberar el escenario
        }
        pair = map_next(grafo);
    }

    map_destroy(grafo); // Liberar el mapa
}