#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

#define HASH_SIZE 100

typedef struct Node {
    int key;
    int value;
    struct Node *prev, *next;
} Node;

typedef struct {
    Node *head, *tail;
    Node *hash[HASH_SIZE];
} Cache;

Cache *create_cache(int size) {
    Cache *cache = (Cache *)malloc(sizeof(Cache));
    cache->head = cache->tail = NULL;
    for (int i = 0; i < HASH_SIZE; i++) cache->hash[i] = NULL;
    return cache;
}

void move_to_head(Cache *cache, Node *node) {
    if (node == cache->head) return;
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (node == cache->tail) cache->tail = node->prev;
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;
}

int cache_lookup(Cache *cache, int key) {
    Node *node = cache->hash[key % HASH_SIZE];
    while (node) {
        if (node->key == key) {
            move_to_head(cache, node);
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

void cache_insert(Cache *cache, int key, int value) {
    Node *node = cache->hash[key % HASH_SIZE];
    while (node) {
        if (node->key == key) {
            node->value = value;
            move_to_head(cache, node);
            return;
        }
        node = node->next;
    }

    node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = cache->hash[key % HASH_SIZE];
    cache->hash[key % HASH_SIZE] = node;
    move_to_head(cache, node);
}

void free_cache(Cache *cache) {
    Node *cur = cache->head;
    while (cur) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    free(cache);
}
