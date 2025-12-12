#include "path_list.h"

//*auxiliary functions
bool create_node_path(t_pos_path *new_node);
//*end of auxiliary functions

void create_empty_list_path(t_list_path *L)
{
    *L = PNULL;
}

bool is_empty_list_path(t_list_path L)
{
    return (L == PNULL);
}

t_pos_path first_path(t_list_path L)
{
    return L;
}

t_pos_path last_path(t_list_path L)
{
    return L->prev;
}

t_pos_path next_path(t_pos_path p, t_list_path L)
{
    UNUSED(L);
    return p->next;
}

t_pos_path previous_path(t_pos_path p, t_list_path L)
{   
    if (p->prev == last_path(L))
    {
        return PNULL;
    }
    else
        return p->prev;
}

bool insert_item_path(t_item_path d, t_pos_path p, t_list_path *L)
{
    t_pos_path new_node;

    if (!create_node_path(&new_node))
        return false;

    new_node->item = d;
    new_node->next = PNULL;
    new_node->prev = PNULL;

    if(is_empty_list_path(*L)){
        *L = new_node;
        new_node->prev = new_node;
    } else if( p == PNULL ) {
        t_pos_path pos;

        pos = (*L)->prev;
        pos->next = new_node;
        new_node->prev = pos;
        (*L)->prev = new_node;
    } else if (p == *L)
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


