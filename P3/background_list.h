#ifndef BACKGROUND_LIST_H
#define BACKGROUND_LIST_H

#include "types.h"

typedef struct t_item_background
{
    int pid;
    time_t time;
    unsigned char status;
    int sin;
    char command_line[MAX_INPUT_SIZE];
}t_item_background;

typedef struct t_node_background
{
    t_item_background data;
    struct t_node_background *next;
    struct t_node_background *prev;
}t_node_background;

typedef t_pos_background t_list_background;

void create_empty_list_background(t_list_background *L);

bool is_empty_list_background(t_list_background L);

t_pos_background first_background(t_list_background L);

t_pos_background last_background(t_list_background L);

t_pos_background next_background(t_pos_background p, t_list_background L);

t_pos_background previous_background(t_pos_background p, t_list_background L);

bool insert_item_background(t_item_background d, t_pos_background p, t_list_background *L);

void delete_at_position_background(t_pos_background p, t_list_background *L);

t_item_background get_item_background(t_pos_background p, t_list_background L);

void update_item_background(t_item_background d, t_pos_background p, t_list_background* L);

#endif // BACKGROUND_LIST_H