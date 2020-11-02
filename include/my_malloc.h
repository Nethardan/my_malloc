#include <unistd.h>
#include <stdbool.h>

typedef struct mem_node {
    struct mem_node *prev;
    struct mem_node *next;
    size_t size;
    bool free;
} mnode_t;

extern mnode_t *ghead;

// memory management functions
void *my_malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

//utils
intptr_t get_padding(intptr_t offset);
intptr_t get_aligned(intptr_t offset);
void print_memory_list(void);
