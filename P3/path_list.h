#ifndef PATH_LIST_H
#define PATH_LIST_H

#include "types.h"

typedef char* t_item_path;

typedef struct t_node_path
{
    t_item_path item;
    struct t_node_path *prev;
    struct t_node_path *next;
}t_node_path;

typedef t_pos_path t_list_path;

void create_empty_list_path(t_list_path *L);
bool is_empty_list_path(t_list_path L);
t_pos_path first_path(t_list_path L);
t_pos_path last_path(t_list_path L);
t_pos_path next_path(t_pos_path p, t_list_path L);
t_pos_path previous_path(t_pos_path p, t_list_path L);
bool insert_item_path(t_item_path d, t_pos_path p, t_list_path *L);
void delete_at_position_path(t_pos_path p, t_list_path *L);
t_item_path get_item_path(t_pos_path p, t_list_path L);
t_pos_path find_item_path(char *path, t_list_path L);

#endif  // PATH_LIST_H