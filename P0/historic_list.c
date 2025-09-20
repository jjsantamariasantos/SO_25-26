#include "historic_list.h"

//*auxiliary functions
bool create_node_historic(t_pos_historic *new_node);
//*end of auxiliary functions

void create_empty_list_historic(t_list_historic *L){
    *L = HNULL;
}

bool is_empty_list_historic(t_list_historic L){
    return (L == HNULL);
}

t_pos_historic first_position_historic(t_list_historic L){
    return L;
}

t_pos_historic last_position_historic(t_list_historic L){
    return L->prev;
}
t_pos_historic next_position_historic(t_pos_historic p, t_list_historic L){
    UNUSED(L);
    return p->next;
}
t_pos_historic previous_position_historic(t_pos_historic p, t_list_historic L){
    UNUSED(L);
    return p->prev;
}

bool insert_item_historic(t_item_historic d, t_pos_historic p, t_list_historic *L){
    t_pos_historic new_node;
    if (!create_node_historic(&new_node))
        return false;
    new_node->item = d;
    new_node->next = HNULL;
    new_node->prev = HNULL;
    if (is_empty_list_historic(*L)){
        *L = new_node;
        new_node->prev = new_node;
    } else if(p == HNULL){  //* insert at the end
        t_pos_historic aux;

        aux = (*L)->prev;
        aux->next = new_node;
        new_node->prev = aux;
        (*L)->prev = new_node;
    } else if(p == *L){    //* insert at the beginning
        new_node->next = *L;
        new_node->prev = (*L)->prev;
        (*L)->prev->next = new_node;
        *L = new_node;
    } else {    //* insert in the middle
    new_node->next = p;
    new_node->prev = p->prev;
    p->prev->next = new_node;
    p->prev = new_node;
    }

    return true;
}
void delete_at_position_historic(t_pos_historic p, t_list_historic *L){
    t_pos_historic aux;
    if (p == *L){   //* first node
        if (p->next == HNULL){  //* only one node
            *L = HNULL;
        }
        else{
            *L = p->next;         
            (*L)->prev = p->prev; 
        }
    } else if (p->next == HNULL){   //* last node
        aux = p->prev;
        (*L)->prev = aux;
        aux->next = HNULL;     
    } else {    //* middle node
        //* pointers are rearranged
        aux = p->next;
        p->prev->next = aux;
        aux->prev = p->prev;
    }

    free(p);
}

void delete_list_historic(t_list_historic *L){
    t_pos_historic aux;
    while ((*L)->next != HNULL){
        aux = *L;   //* save current node to not lose reference in the free operation
        *L = (*L)->next;
        free(aux);
    }
    *L = HNULL;
}

t_item_historic get_item_historic(t_pos_historic p, t_list_historic L){
    UNUSED(L);
    return p->item;
}

bool create_node_historic(t_pos_historic *new_node){
    *new_node = (t_pos_historic)malloc(sizeof(struct t_node_historic));
    if (*new_node == NULL)
    {
        return false;
    }

    return true;
}