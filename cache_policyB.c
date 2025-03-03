/* cache_policyB.c */
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

#define CACHE_SIZE 100

typedef struct {
    int keys[CACHE_SIZE];
    int values[CACHE_SIZE];
    int start, count;
} Cache;

Cache *create_cache(int size) {
    Cache *cache = (Cache *)malloc(sizeof(Cache));
    cache->start = cache->count = 0;
    return cache;
}

int cache_lookup(Cache *cache, int key) {
    for (int i = 0; i < cache->count; i++) {
        if (cache->keys[(cache->start + i) % CACHE_SIZE] == key) {
            return cache->values[(cache->start + i) % CACHE_SIZE];
        }
    }
    return -1;
}

void cache_insert(Cache *cache, int key, int value) {
    if (cache->count < CACHE_SIZE) {
        int index = (cache->start + cache->count) % CACHE_SIZE;
        cache->keys[index] = key;
        cache->values[index] = value;
        cache->count++;
    } else {
        cache->keys[cache->start] = key;
        cache->values[cache->start] = value;
        cache->start = (cache->start + 1) % CACHE_SIZE;
    }
}

void free_cache(Cache *cache) {
    free(cache);
}
