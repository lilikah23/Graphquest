#include <stdio.h>
#include "base/estructura.h"
#include "base/funciones.h"
#include "tdas/map.h"
#include "tdas/extra.h"
#include <locale.h>

int main() {
    // Configurar la localización para manejar caracteres especiales, que tenga el csv
    setlocale(LC_ALL, "");
    
    int opcion_pre;
    do {
        limpiarPantalla();
        printf("====== Graphquest ======\n");
        printf("1. Inicia la partida\n");
        printf("2. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion_pre);

        if (opcion_pre == 2) {
            printf("Gracias por jugar GraphQuest.\n");
            return 0;
        }
        if (opcion_pre != 1) {
            printf("Opcion invalida.\n");
        }
    } while (opcion_pre != 1);

    int id_inicio = -1;
// Cargar el laberinto desde el archivo CSV
// y obtener el ID de inicio
Map *grafo = cargar_laberinto("data/graphquest.csv", &id_inicio);

if (grafo == NULL) {
    printf("Error al cargar el laberinto.\n");
    return 1;
}

// Buscar el escenario de menor ID como inicio
MapPair *pair = map_first(grafo);
if (!pair) {
    printf("No hay escenarios en el laberinto.\n");
    return 1;
}
int min_id = ((Escenario*)pair->value)->id;
for (; pair; pair = map_next(grafo)) {
    Escenario *esc = (Escenario*)pair->value;
    if (esc->id < min_id) min_id = esc->id;
}
id_inicio = min_id;

Jugador *jugador = crear_jugador(10, id_inicio);

int opcion;
do {
    MapPair *pair = map_get(grafo, &jugador->escenario_actual_id);
    Escenario *actual = pair ? (Escenario *)pair->value : NULL;
    limpiarPantalla();
    if (!actual) {
        printf("Error: escenario actual no encontrado.\n");
        break;
    }
    mostrar_estado(jugador, actual);
    printf("\n========== MENU DE JUEGO ==========\n");
    printf("1. Recoger items\n");
    printf("2. Descartar items\n");
    printf("3. Avanzar (moverse)\n");
    printf("4. Reiniciar jugador\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion aventurero: ");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            recoger_items(jugador, actual);
            break;
        case 2:
            descartar_items(jugador);
            break;
        case 3: {
            printf("Direcciones:\n0 = Arriba, 1 = Abajo, 2 = Izquierda, 3 = Derecha\n");
            printf("Ingrese direccion: ");
            int dir;
            scanf("%d", &dir);
            if (avanzar(jugador, grafo, dir)) {
                limpiarPantalla();
                MapPair *new_pair = map_get(grafo, &jugador->escenario_actual_id);
                Escenario *new_actual = new_pair ? (Escenario *)new_pair->value : NULL;
                if (new_actual) mostrar_estado(jugador, new_actual);
            } else {
                presioneTeclaParaContinuar();
            }
            break;
        }
        case 4:
            reiniciar_jugador(jugador, 10, id_inicio);
            break;
        case 0:
            printf("Gracias por jugar GraphQuest.\n");
            presioneTeclaParaContinuar();
            limpiarPantalla();
            break;
        default:
            printf("Opcion invalida.\n");
    }
} while (opcion != 0);

// Liberar memoria
destruir_jugador(jugador);

return 0;
}