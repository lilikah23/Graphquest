#ifndef MAP_H
#define MAP_H

typedef struct Map Map;
typedef struct MapPair {
    void *key;
    void *value;
} MapPair;

Map *map_create(int (*is_equal)(void *key1, void *key2));
void map_insert(Map *map, void *key, void *value);
MapPair *map_search(Map *map, void *key);
MapPair *map_first(Map *map);
MapPair *map_next(Map *map);
MapPair *map_get(Map *map, void *key);
void map_destroy(Map *map);

#endif