#include "mem_list.h"

//*auxiliary functions
bool create_node_mem(t_pos_mem *new_node);
//*end of auxiliary functions

void create_empty_list_mem(t_list_mem *L)
{
    *L = MNULL;
}

bool is_empty_list_mem(t_list_mem L)
{
    return (L == MNULL);
}

t_pos_mem first_mem(t_list_mem L)
{
    return L;
}

t_pos_mem last_mem(t_list_mem L)
{
    return L->prev;
}

t_pos_mem previous_mem(t_pos_mem p, t_list_mem L)
{   
    if (p->prev == last_mem(L))
    {
        return MNULL;
    }
    else
        return p->prev;
}
t_pos_mem next_mem(t_pos_mem p, t_list_mem L)
{   
    UNUSED(L);
    return p->next;
}

bool insert_item_mem(t_item_mem d, t_pos_mem p, t_list_mem *L)
{
    t_pos_mem new_node;

    if (!create_node_mem(&new_node))
        return false;

    new_node->item = d;
    new_node->next = MNULL;
    new_node->prev = MNULL;

    if (is_empty_list_mem(*L))
    {
        *L = new_node;
        new_node->prev = new_node;
    }
    else if (p == MNULL)
    {
        t_pos_mem last = last_mem(*L);
        last->next = new_node;
        new_node->prev = last;
        (*L)->prev = new_node;
    }
    else if (p == *L)
    {
        new_node->next = *L;
        new_node->prev = (*L)->prev;
        (*L)->prev = new_node;
        *L = new_node;
    }
    else
    {
        new_node->next = p;
        new_node->prev = p->prev;
        p->prev->next = new_node;
        p->prev = new_node;
    }
    return true;
}

void delete_at_position_mem(t_pos_mem p, t_list_mem *L)
{
    t_pos_mem to_delete;

    if(p==*L){
        if(p->next==MNULL){
            *L = MNULL;
        } else {
            *L = p->next;
            (*L)->prev = p->prev;
        }
    } else if(p->next==MNULL){
        to_delete = p->prev;
        (*L)->prev = to_delete;
        to_delete->next = MNULL;
    } else {
        to_delete = p->next;
        p->prev->next = to_delete;
        to_delete->prev = p->prev;
    }
    free(p);
}

t_item_mem get_item_mem(t_pos_mem p, t_list_mem L)
{
    UNUSED(L);
    return p->item;
}

bool create_node_mem(t_pos_mem *new_node)
{
    *new_node = malloc(sizeof(t_node_mem));
    if (*new_node == NULL)
        return false;
    return true;
}

t_pos_mem find_item_mem_by_addr(void *addr, t_list_mem L)
{
    if( is_empty_list_mem(L) )
        return MNULL;
    t_pos_mem pos = L;

    while(pos != MNULL) {
        if(pos->item.addr == addr)
            return pos;
        pos = pos->next;
        
    }
    return MNULL;
}

t_pos_mem find_item_malloc_mem_by_size(size_t size, t_list_mem L)
{
    if( is_empty_list_mem(L) )
        return MNULL;
    unsigned char type_malloc = M_MALLOC;
    t_pos_mem pos = L;

    while(pos != MNULL) {
        if(pos->item.size == size && (pos->item.type & type_malloc))
            return pos;
        pos = pos->next;
        
    }
    return MNULL;
    
}

t_pos_mem find_item_mmap_mem_by_name(char *name, t_list_mem L)
{
    if( is_empty_list_mem(L) )
        return MNULL;
    unsigned char type_mmap = M_MMAP;
    t_pos_mem pos = L;

    while(pos != MNULL) {
        if(strcmp(pos->item.name, name) == 0 && (pos->item.type & type_mmap))
            return pos;
        pos = pos->next;
        
    }
    return MNULL;
}

t_pos_mem find_item_shared_mem_by_key(int key, t_list_mem L)
{
    if( is_empty_list_mem(L) )
        return MNULL;
    unsigned char type_shared = M_SHARED;
    t_pos_mem pos = L;

    while(pos != MNULL) {
        if(pos->item.key == key && (pos->item.type & type_shared))
            return pos;
        pos = pos->next;
        
    }
    return MNULL;
}
