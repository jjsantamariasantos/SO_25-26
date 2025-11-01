#ifndef MEM_LIST_H
#define MEM_LIST_H

#include "types.h"

typedef struct t_item_mem
{
    unsigned char type;
    void *addr;
    size_t size;
    time_t date;
    char name[MAX_INPUT_SIZE];
    int key;
} t_item_mem;

struct t_node_mem
{
    t_item_mem item;
    struct t_node_mem *prev;
    struct t_node_mem *next;
} t_node_mem;

typedef t_pos_mem t_list_mem;

void create_empty_list_mem(t_list_mem *L);
bool is_empty_list_mem(t_list_mem L);
t_pos_mem first_mem(t_list_mem L);
t_pos_mem last_mem(t_list_mem L);
t_pos_mem next_mem(t_pos_mem p, t_list_mem L);
t_pos_mem previous_mem(t_pos_mem p, t_list_mem L);
bool insert_item_mem(t_item_mem d, t_pos_mem p, t_list_mem *L);
void delete_at_position_mem(t_pos_mem p, t_list_mem *L);
t_item_mem get_item_mem(t_pos_mem p, t_list_mem L);
t_pos_mem find_item_mem_by_addr(void *addr, t_list_mem L);
t_pos_mem find_item_malloc_mem_by_size(size_t size, t_list_mem L);
t_pos_mem find_item_mmap_mem_by_name(char *name, t_list_mem L);
t_pos_mem find_item_shared_mem_by_key(int key, t_list_mem L);

#endif /*MEM_LIST_H*/