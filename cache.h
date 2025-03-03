#ifndef CACHE_H
#define CACHE_H

typedef struct CacheEntry {
    int key;
    int value;
    struct CacheEntry *next;
} CacheEntry;

typedef struct {
    CacheEntry **table;
    int size;
} Cache;

Cache *create_cache(int size);
void cache_insert(Cache *cache, int key, int value);
int cache_lookup(Cache *cache, int key);
void free_cache(Cache *cache);

#endif
