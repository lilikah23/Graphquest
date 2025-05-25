#include <stdlib.h>
#include "list.h"

struct Node {
    void *data;
    Node *next;
};

struct List {
    Node *head;
    Node *current;
};

List *list_create() {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->current = NULL;
    return list;
}

void list_pushBack(List *list, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *ptr = list->head;
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = newNode;
    }
}

void *list_first(List *list) {
    if (!list->head) return NULL;
    list->current = list->head;
    return list->current->data;
}

void *list_next(List *list) {
    if (!list->current || !list->current->next) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void list_clean(List *list) {
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->current = NULL;
}

void list_destroy(List *list) {
    list_clean(list);
    free(list);
}

void list_get(List *list, int index, void *data) {
    if (index < 0 || !list->head) return;

    Node *ptr = list->head;
    for (int i = 0; i < index && ptr != NULL; i++) {
        ptr = ptr->next;
    }

    if (ptr) {
        *((void **)data) = ptr->data;
    } else {
        *((void **)data) = NULL;
    }
}

int list_size(List *list) {
    int size = 0;
    Node *ptr = list->head;
    while (ptr) {
        size++;
        ptr = ptr->next;
    }
    return size;
}

void list_remove(List *list, int index) {
    if (index < 0 || list->head == NULL) return;

    Node *ptr = list->head;
    Node *prev = NULL;

    for (int i = 0; i < index && ptr != NULL; i++) {
        prev = ptr;
        ptr = ptr->next;
    }

    if (ptr) {
        if (prev) {
            prev->next = ptr->next;
        } else {
            list->head = ptr->next;
        }
        free(ptr);
    }
}

