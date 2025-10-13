/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#ifndef FILE_LIST_H
#define FILE_LIST_H

#include "types.h"

#define FNULL NULL

typedef struct t_item_file{
    int fd;
    char file_name[MAX_INPUT_SIZE];
    int mode;
} t_item_file;

typedef struct t_node_file{
    t_item_file item;
    struct t_node_file *prev;
    struct t_node_file *next;
} t_node_file;

typedef t_pos_file t_list_file;

void create_empty_list_file(t_list_file *L);
bool is_empty_list_file(t_list_file L);
t_pos_file first_file(t_list_file L);
t_pos_file last_file(t_list_file L);
t_pos_file next_file(t_pos_file p, t_list_file L);
t_pos_file previous_file(t_pos_file p, t_list_file L);
bool insert_item_file(t_item_file d, t_pos_file p, t_list_file *L);
void delete_at_position_file(t_pos_file p, t_list_file *L);
void update_item_file(t_item_file d, t_pos_file p, t_list_file *L);
t_item_file get_item_file(t_pos_file p, t_list_file L);
t_pos_file find_item_file(int fd, t_list_file L);

#endif  /*FILE_LIST_H*/