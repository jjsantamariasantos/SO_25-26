#ifndef HISTORIC_LIST_H
#define HISTORIC_LIST_H

#include "types.h"

#define HNULL NULL

typedef struct t_item_historic{
    char *command[MAX_INPUT_SIZE];
    int num_command;
} t_item_historic;

typedef struct t_node_historic{
    t_item_historic item;
    struct t_node_historic *prev;
    struct t_node_historic *next;
} t_node;

typedef t_pos_historic t_list_historic;

void create_empty_list_historic(t_list_historic *L);
bool is_empty_list_historic(t_list_historic L);
t_pos_historic first_position_historic(t_list_historic L);
t_pos_historic last_position_historic(t_list_historic L);
t_pos_historic next_position_historic(t_pos_historic p, t_list_historic L);
t_pos_historic previous_position_historic(t_pos_historic p, t_list_historic L);
bool insert_item_historic(t_item_historic d, t_pos_historic p, t_list_historic *L);
void delete_at_position_historic(t_pos_historic p, t_list_historic *L);
void delete_list_historic(t_list_historic *L);
t_item_historic get_item_historic(t_pos_historic p, t_list_historic L);

#endif /*HISTORIC_LIST_H*/