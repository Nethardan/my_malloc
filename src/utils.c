#include "my_malloc.h"
#include <stdio.h>

intptr_t get_padding(intptr_t offset)
{
    intptr_t align = 2;

    return ((align - (offset % align)) % align);
}

intptr_t get_aligned(intptr_t offset)
{
    return (offset + get_padding(offset));
}

void print_memory_list(void)
{
    bool loop = false;

    if (!ghead)
        return;
    for (mnode_t *temp = ghead; temp != ghead || !loop; temp= temp->next) {
        if (temp == ghead)
            loop = true;
        printf("####### %s #######\naddress = %p\nprev = %p\nnext = %p\nsize = %ld\nfree = %s\n\n",
        temp == ghead ? "HEAD" : (temp->next == ghead ? "TAIL" : "NODE"), temp,
        temp->prev, temp->next, temp->size,
        temp->free ? "True" : "False");
    }
}