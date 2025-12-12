#include "background_list.h"

bool createNodeB(t_pos_background *p);

void create_empty_list_background(t_list_background *L)
{
    *L = BNULL;
}

bool is_empty_list_background(t_list_background L)
{
    return L == BNULL;
}

t_pos_background first_background(t_list_background L)
{
    return L;
}

t_pos_background last_background(t_list_background L)
{
    return L->prev;
}

t_pos_background previous_background(t_pos_background p, t_list_background L)
{
    if (p->prev == last_background(L))
    {
        return BNULL;
    }
    else
        return p->prev;
}

t_pos_background next_background(t_pos_background p, t_list_background L)
{
    UNUSED(L);
    return p->next;
}

bool insert_item_background(t_item_background d, t_pos_background p, t_list_background *L)
{
    t_pos_background q;

    if (!createNodeB(&q))
        return false;

    q->data = d;
    q->next = BNULL;
    q->prev = BNULL;

    if (is_empty_list_background(*L)) 
    {
        *L = q; 
        q->prev = q;
    }
    else if (p == BNULL) 
    {
        t_pos_background r;

        r = (*L)->prev; 
        r->next = q;
        q->prev = r;
        (*L)->prev = q;
    }
    else if (p == *L) 
    {
        q->next = *L;
        q->prev = (*L)->prev; 
        (*L)->prev = q;
        *L = q;
    }
    else 
    {
       
        q->next = p;
        q->prev = p->prev;
        p->prev->next = q;
        p->prev = q;
    }
    return true;
}

void delete_at_position_background(t_pos_background p, t_list_background *L)
{
    t_pos_background q;

    if (p == *L) 
    {
        if (p->next == BNULL)
        {
            *L = BNULL;
        }
        else
        {
            *L = p->next;         
            (*L)->prev = p->prev; 
        }
    }
    else if (p->next == BNULL) 
    {
        q = p->prev;
        (*L)->prev = q;
        q->next = BNULL;
    }
    else 
    {
        q = p->next;
        p->prev->next = q;
        q->prev = p->prev;
    }

    free(p);
}

t_item_background get_item_background(t_pos_background p, t_list_background L)
{
    UNUSED(L);
    return (p->data);
}

bool createNodeB(t_pos_background *p)
{
    *p = malloc(sizeof(struct t_node_background));
    if (*p == BNULL)
        return false;
    else
        return true;
}

void update_item_background(t_item_background d, t_pos_background p, t_list_background* L)
{
    UNUSED(L);
    p->data=d;
}