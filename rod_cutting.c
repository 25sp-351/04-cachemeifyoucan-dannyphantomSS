/* rod_cutting.c */
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

#define MAX_LENGTH 10000

typedef struct {
    int length;
    int value;
    int max_count; // Extra Credit
} RodPiece;

RodPiece pieces[MAX_LENGTH];
int size = 0;

void read_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    while (fscanf(file, "%d %d %d", &pieces[size].length, &pieces[size].value, &pieces[size].max_count) == 3) {
        size++;
    }
    fclose(file);
}

int rod_cut(int length, Cache *cache) {
    if (length == 0) return 0;
    if (cache_lookup(cache, length) != -1) return cache_lookup(cache, length);
    
    int max_value = 0;
    for (int i = 0; i < size; i++) {
        if (pieces[i].length <= length) {
            int count = (pieces[i].max_count == 0) ? (length / pieces[i].length) : pieces[i].max_count;
            for (int j = 1; j <= count; j++) {
                int val = j * pieces[i].value + rod_cut(length - j * pieces[i].length, cache);
                if (val > max_value) max_value = val;
            }
        }
    }
    cache_insert(cache, length, max_value);
    return max_value;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    read_file(argv[1]);
    
    Cache *cache = create_cache(100);
    int length;
    while (scanf("%d", &length) == 1) {
        printf("Max value for length %d: %d\n", length, rod_cut(length, cache));
    }
    free_cache(cache);
    return 0;
}
