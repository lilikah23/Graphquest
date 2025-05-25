#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../base/estructura.h"
#include "../base/funciones.h"
#include "../tdas/map.h"
#include "../tdas/list.h"
#include "../tdas/extra.h"

// Función para parsear una línea CSV respetando comillas
int split_csv(const char *str, char **result, int max_fields) {
    int count = 0, in_quotes = 0;
    const char *start = str;
    char *field;
    size_t len;
    while (*str && count < max_fields) {
        if (*str == '"') in_quotes = !in_quotes;
        else if (*str == ',' && !in_quotes) {
            len = str - start;
            field = (char *)malloc(len + 1);
            strncpy(field, start, len);
            field[len] = '\0';
            // Elimina comillas si existen
            if (field[0] == '"' && field[len-1] == '"') {
                field[len-1] = '\0';
                memmove(field, field+1, len-1);
            }
            result[count++] = field;
            start = str + 1;
        }
        str++;
    }
    // Último campo
    if (count < max_fields) {
        len = str - start;
        field = (char *)malloc(len + 1);
        strncpy(field, start, len);
        field[len] = '\0';
        if (field[0] == '"' && field[len-1] == '"') {
            field[len-1] = '\0';
            memmove(field, field+1, len-1);
        }
        result[count++] = field;
    }
    return count;
}
// Función para cargar el laberinto desde un archivo CSV
// y devolver un grafo de escenarios
Map *cargar_laberinto(const char *archivo_csv, int *id_inicio) {
    FILE *archivo = fopen(archivo_csv, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }

    Map *grafo = map_create(int_cmp);
    char linea[1024];
    fgets(linea, sizeof(linea), archivo); // Leer encabezado

    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\r\n")] = 0; // Elimina salto de línea

        char *campos[10];
        int n = split_csv(linea, campos, 10);
        if (n < 9) {
            for (int i = 0; i < n; i++) free(campos[i]);
            continue; // Línea mal formada
        }

        Escenario *esc = malloc(sizeof(Escenario));
        esc->id = atoi(campos[0]);
        strcpy(esc->nombre, campos[1]);
        strcpy(esc->descripcion, campos[2]);
        esc->items = list_create();

        // Cargar ítems
        if (strlen(campos[3]) > 0) {
            List *items_raw = split_dyn(campos[3], ";");
            for (char *item_str = list_first(items_raw); item_str; item_str = list_next(items_raw)) {
                char *valores[3];
                int total = split(item_str, valores, 3, ",");
                if (total < 3) continue;

                Item *item = malloc(sizeof(Item));
                strcpy(item->nombre, valores[0]);
                item->valor = atoi(valores[1]);
                item->peso = atoi(valores[2]);
                list_pushBack(esc->items, item);
            }
            list_destroy(items_raw);
        }

        esc->conexiones[0] = atoi(campos[4]);
        esc->conexiones[1] = atoi(campos[5]);
        esc->conexiones[2] = atoi(campos[6]);
        esc->conexiones[3] = atoi(campos[7]);
        esc->es_final = (strcmp(campos[8], "Si") == 0 || strcmp(campos[8], "si") == 0 || strcmp(campos[8], "1") == 0) ? 1 : 0;

        map_insert(grafo, &(esc->id), esc);

        for (int i = 0; i < n; i++) free(campos[i]);
    }

    fclose(archivo);
    return grafo;
}

// Funcion para crear un jugador
// Inicia el tiempo, inventario, peso total, puntaje total y escenario actual
Jugador *crear_jugador(int tiempo, int id_inicio) {
    Jugador *j = malloc(sizeof(Jugador));
    j->tiempo_restante = tiempo;
    j->inventario = list_create();
    j->peso_total = 0;
    j->puntaje_total = 0;
    j->escenario_actual_id = id_inicio;
    return j;
}

// Funcion para mostrar el estado del jugador
// Muestra el tiempo restante, peso total, puntaje total, escenario actual y los items en el escenario y en el inventario
void mostrar_estado(Jugador *jugador, Escenario *escenario) {
    printf("=== Estado del Jugador ===\n");
    printf("Tiempo restante: %d\n", jugador->tiempo_restante);
    printf("Peso total: %d\n", jugador->peso_total);
    printf("Puntaje total: %d\n", jugador->puntaje_total);
    printf("Escenario actual: %s\n", escenario->nombre);
    printf("Descripcion: %s\n", escenario->descripcion);

    // Mostrar caminos disponibles
    printf("Caminos disponibles: ");
    if (escenario->conexiones[0] != -1) printf("[0: Arriba] ");
    if (escenario->conexiones[1] != -1) printf("[1: Abajo] ");
    if (escenario->conexiones[2] != -1) printf("[2: Izquierda] ");
    if (escenario->conexiones[3] != -1) printf("[3: Derecha] ");
    printf("\n");

    printf("Items en el escenario:\n");
    for (Item *item = list_first(escenario->items); item; item = list_next(escenario->items)) {
        printf("- %s (valor: %d, peso: %d)\n", item->nombre, item->valor, item->peso);
    }

    printf("\nInventario:\n");
    for (Item *item = list_first(jugador->inventario); item; item = list_next(jugador->inventario)) {
        printf("- %s (valor: %d, peso: %d)\n", item->nombre, item->valor, item->peso);
    }
    printf("==========================\n");
}

// Funciones para recoger items 
// Recoge un item del escenario y lo añade al inventario del jugador
void recoger_items(Jugador *jugador, Escenario *escenario) {
    if (list_size(escenario->items) == 0) {
        printf("No hay items para recoger.\n");
        return;
    }

    int i = 1;
    for (Item *item = list_first(escenario->items); item; item = list_next(escenario->items)) {
        printf("%d. %s (valor: %d, peso: %d)\n", i++, item->nombre, item->valor, item->peso);
    }

    printf("Seleccione el numero del item a recoger (0 para cancelar): ");
    int opcion;
    scanf("%d", &opcion);

    if (opcion <= 0 || opcion > list_size(escenario->items)) return;

    Item *item;
    list_get(escenario->items, opcion - 1, &item);
    jugador->peso_total += item->peso;
    jugador->puntaje_total += item->valor;
    list_pushBack(jugador->inventario, item);
    list_remove(escenario->items, opcion - 1);

    printf("Item recogido: %s\n", item->nombre);
}

// Funcion para descartar items
// Descarta un item del inventario del jugador
void descartar_items(Jugador *jugador) {
    if (list_size(jugador->inventario) == 0) {
        printf("Inventario vacio.\n");
        return;
    }

    int i = 1;
    for (Item *item = list_first(jugador->inventario); item; item = list_next(jugador->inventario)) {
        printf("%d. %s (valor: %d, peso: %d)\n", i++, item->nombre, item->valor, item->peso);
    }

    printf("Seleccione el numero del item a descartar (0 para cancelar): ");
    int opcion;
    scanf("%d", &opcion);

    if (opcion <= 0 || opcion > list_size(jugador->inventario)) return;

    Item *item;
    list_get(jugador->inventario, opcion - 1, &item);
    jugador->peso_total -= item->peso;
    jugador->puntaje_total -= item->valor;
    free(item);
    list_remove(jugador->inventario, opcion - 1);

    printf("Item descartado.\n");
}

// Funcion para avanzar a otro escenario
// Verifica si hay una conexion en la direccion indicada
int avanzar(Jugador *jugador, Map *grafo, int direccion) {
    MapPair *pair = map_get(grafo, &jugador->escenario_actual_id);
    if (!pair) {
        printf("No se encontro el escenario actual.\n");
        return 0;
    }
    Escenario *actual = (Escenario *)pair->value;
    int siguiente_id = actual->conexiones[direccion];

    if (siguiente_id == -1) {
        printf("No hay conexion en esa direccion.\n");
        return 0;
    }

    int tiempo_usado = (int)ceil((jugador->peso_total + 1) / 10.0);
    jugador->tiempo_restante -= tiempo_usado;

    if (jugador->tiempo_restante <= 0) {
        printf("Te has quedado sin tiempo. Fin del juego.\n");
        exit(0);
    }

    jugador->escenario_actual_id = siguiente_id;
    return 1;
}

// Funcion para reiniciar el jugador
// Reinicia el tiempo, inventario, peso total, puntaje total y escenario actual
void reiniciar_jugador(Jugador *jugador, int tiempo, int id_inicio) {
    jugador->tiempo_restante = tiempo;
    jugador->peso_total = 0;
    jugador->puntaje_total = 0;
    jugador->escenario_actual_id = id_inicio;

    for (Item *item = list_first(jugador->inventario); item; item = list_next(jugador->inventario)) {
        free(item);
    }

    list_clean(jugador->inventario);
}

// Funcion para destruir el jugador
// Libera la memoria del inventario y del jugador
void destruir_jugador(Jugador *jugador) {
    for (Item *item = list_first(jugador->inventario); item; item = list_next(jugador->inventario)) {
        free(item);
    }
    list_destroy(jugador->inventario);
    free(jugador);
}