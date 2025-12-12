#ifndef BACKGROUND_LIST_H
#define BACKGROUND_LIST_H

#include "types.h"

#define BNULL NULL
#define S_ACTIVE   (1 << 0)  // 0001 (1)
#define S_FINISHED (1 << 1)  // 0010 (2)
#define S_SIGNALED (1 << 2)  // 0100 (4)
#define S_STOPPED  (1 << 4)  // 1000 (8)
#define S_ACTIVE_STOPED (S_ACTIVE | S_STOPPED) // 1100 (12)

typedef struct t_item_background
{
    int pid;
    time_t time;
    unsigned char status;
    int sin;
    char command_line[MAX_INPUT_SIZE];
}t_item_background;

struct t_node_background
{
    t_item_background data;
    struct t_node_background *next;
    struct t_node_background *prev;
}t_node_background;

typedef t_pos_background t_list_background;

void createEmptyListB(t_list_background *L);

bool isEmptyListB(t_list_background L);

t_pos_background firstB(t_list_background L);

t_pos_background lastB(t_list_background L);

t_pos_background nextB(t_pos_background p, t_list_background L);

t_pos_background previousB(t_pos_background p, t_list_background L);

bool insertItemB(t_item_background d, t_pos_background p, t_list_background *L);

void deleteAtPositionB(t_pos_background p, t_list_background *L);

t_item_background getItemB(t_pos_background p, t_list_background L);

void updateItemB(t_item_background d, t_pos_background p, t_list_background* L);

#endif // BACKGROUND_LIST_H