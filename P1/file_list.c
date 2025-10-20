/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#include "file_list.h"

//*auxiliary functions
bool create_node_file(t_pos_file *new_node);
//*end auxiliary functions

void create_empty_list_file(t_list_file *L)
{
    *L = FNULL;
}

bool is_empty_list_file(t_list_file L)
{
    return (L == FNULL);
}

t_pos_file first_file(t_list_file L)
{
    return L;
}

t_pos_file last_file(t_list_file L)
{
    return L->prev;
}

t_pos_file next_file(t_pos_file p, t_list_file L)
{
    UNUSED(L);
    return p->next;
}

t_pos_file previous_file(t_pos_file p, t_list_file L)
{
    UNUSED(L);
    return p->prev;
}

bool insert_item_file(t_item_file d, t_pos_file p, t_list_file *L)
{
    t_pos_file new_node;

    if (!create_node_file(&new_node))
        return false;

    new_node->item = d;
    new_node->next = FNULL;
    new_node->prev = FNULL;

    if (is_empty_list_file(*L))
    {
        *L = new_node;
        new_node->prev = new_node;
    }
    else if (p == FNULL)
    { //* insert at the end
        t_pos_file aux;

        aux = (*L)->prev;
        aux->next = new_node;
        new_node->prev = aux;
        (*L)->prev = new_node;
    }
    else if (p == *L)
    { //* insert at the beginning
        new_node->next = *L;
        new_node->prev = (*L)->prev;
        (*L)->prev->next = new_node;
        *L = new_node;
    }
    else
    { //* insert in the middle
        //* pointers are rearranged
        new_node->next = p;
        new_node->prev = p->prev;
        p->prev->next = new_node;
        p->prev = new_node;
    }

    return true;
}

void delete_at_position_file(t_pos_file p, t_list_file *L)
{
    t_pos_file aux;
    if (p == *L)
    { //* first node
        if (p->next == FNULL)
        { //* only one node
            *L = FNULL;
        }
        else
        {
            *L = p->next;
            (*L)->prev = p->prev;
        }
    }
    else if (p->next == FNULL)
    { //* last node
        aux = p->prev;
        (*L)->prev = aux;
        aux->next = FNULL;
    }
    else
    { //* middle node
        aux = p->next;
        p->prev->next = aux;
        aux->prev = p->prev;
    }

    free(p);
}

void update_item_file(t_item_file d, t_pos_file p, t_list_file *L)
{
    UNUSED(L);
    p->item = d;
}

t_item_file get_item_file(t_pos_file p, t_list_file L)
{
    UNUSED(L);
    return p->item;
}

t_pos_file find_item_file(int fd, t_list_file L)
{
    t_pos_file aux;

    for (aux = L; (aux != FNULL) && (aux->item.fd != fd); aux = aux->next);
    return aux;
}

bool create_node_file(t_pos_file *new_node)
{
    *new_node = (t_pos_file)malloc(sizeof(struct t_node_file));
    if (*new_node == NULL)
    {
        return false;
    }

    return true;
}