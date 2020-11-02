#include "my_malloc.h"

mnode_t *ghead = NULL;

size_t get_total_allocation_size(size_t size)
{
    size_t total_size = size + sizeof(mnode_t) + (sizeof(mnode_t) + get_padding(size)) * ((((size + sizeof(mnode_t)) % getpagesize()) != 0));
    intptr_t total_allocation = getpagesize() * (total_size / getpagesize() + (total_size % getpagesize() != 0));

    printf("total_size : %d\ntotal_allocation : %d\n", total_size, total_allocation);
    return (total_allocation);
}

void create_free_node(mnode_t *temp, size_t size, size_t total_allocation)
{
    temp->next = (mnode_t *)get_aligned((intptr_t) temp + sizeof(mnode_t) + size);
    temp->next->free = true;
    temp->next->size = total_allocation - ((intptr_t) sbrk(0) - (intptr_t) temp->next) - sizeof(mnode_t);
    temp->next->prev = temp;
    if (!ghead) {
        temp->next->next = temp;
        temp->prev = temp->next;
    } else {
        temp->next->next = ghead;
        temp->prev = ghead->prev;
        temp->prev->next = temp;
        ghead->prev = temp->next;
    }
}

void *extand_break(size_t size)
{
    size_t total_allocation = get_total_allocation_size(size);
    mnode_t *temp = sbrk(total_allocation);

    temp->size = size;
    temp->free = false;
    temp->next = temp;
    temp->prev = temp;
    if (((size + sizeof(mnode_t)) % getpagesize()) != 0)
        create_free_node(temp, size, total_allocation);
    else if (ghead) {
        temp->next = ghead;
        temp->prev = ghead->prev;
        temp->prev->next = temp;
        ghead->prev = temp;
    }
    if (!ghead)
        ghead = temp;
    return ((intptr_t *)temp + sizeof(mnode_t));
}

void *get_best_fit_node(size_t size)
{
    return (NULL);
}

void *allocation(size_t size)
{
    void *node = get_best_fit_node(size);

    if (!node)
        return (extand_break(size));
    return (NULL);
}

void *my_malloc(size_t size)
{
    if (size == 0)
        return (NULL);
    if (!ghead)
        return (extand_break(size));
    else
        return (allocation(size));
    return (NULL);
}