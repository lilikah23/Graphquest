#include <stdlib.h>
#include "map.h"

#define CAPACITY 500

typedef struct PairNode {
    MapPair *pair;
    struct PairNode *next;
} PairNode;

struct Map {
    PairNode *buckets[CAPACITY];
    int current_bucket;
    PairNode *current_node;
    int (*is_equal)(void *key1, void *key2);
};

static unsigned long hash_function(void *key) {
    char *str = key;
    unsigned long hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (*str++);
    }
    return hash % CAPACITY;
}

Map *map_create(int (*is_equal)(void *key1, void *key2)) {
    Map *map = malloc(sizeof(Map));
    for (int i = 0; i < CAPACITY; i++)
        map->buckets[i] = NULL;
    map->is_equal = is_equal;
    map->current_bucket = -1;
    map->current_node = NULL;
    return map;
}

void map_insert(Map *map, void *key, void *value) {
    unsigned long idx = hash_function(key);
    PairNode *node = malloc(sizeof(PairNode));
    MapPair *pair = malloc(sizeof(MapPair));
    pair->key = key;
    pair->value = value;
    node->pair = pair;
    node->next = map->buckets[idx];
    map->buckets[idx] = node;
}

MapPair *map_search(Map *map, void *key) {
    unsigned long idx = hash_function(key);
    PairNode *node = map->buckets[idx];
    while (node != NULL) {
        if (map->is_equal(node->pair->key, key)) {
            return node->pair;
        }
        node = node->next;
    }
    return NULL;
}

MapPair *map_first(Map *map) {
    for (int i = 0; i < CAPACITY; i++) {
        if (map->buckets[i]) {
            map->current_bucket = i;
            map->current_node = map->buckets[i];
            return map->current_node->pair;
        }
    }
    return NULL;
}

MapPair *map_next(Map *map) {
    if (map->current_node && map->current_node->next) {
        map->current_node = map->current_node->next;
        return map->current_node->pair;
    }
    for (int i = map->current_bucket + 1; i < CAPACITY; i++) {
        if (map->buckets[i]) {
            map->current_bucket = i;
            map->current_node = map->buckets[i];
            return map->current_node->pair;
        }
    }
    return NULL;
}

MapPair *map_get(Map *map, void *key) {
    return map_search(map, key);
}

void map_destroy(Map *map) {
    if (!map) return;
    for (int i = 0; i < CAPACITY; i++) {
        PairNode *node = map->buckets[i];
        while (node) {
            PairNode *next = node->next;
            free(node->pair); // libera el MapPair
            free(node);       // libera el nodo
            node = next;
        }
    }
    free(map);
}