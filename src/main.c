#include <stdio.h>
#include "my_malloc.h"

void *my_malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

int main(int ac, char **av)
{
    my_malloc(4063);
    my_malloc(4063);
    print_memory_list();
    printf("page size = %d\nmnode_t size = %ld\n", getpagesize(), sizeof(mnode_t));
    return (0);
}