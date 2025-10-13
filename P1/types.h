/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/utsname.h>

#include "macros.h"
typedef struct type_args
{
    char *input[ARGS_MAX];
    int length;
} type_args;

//* forward declaration for list
typedef struct t_node_historic *t_pos_historic;
typedef t_pos_historic t_list_historic;

typedef struct t_node_file *t_pos_file;
typedef t_pos_file t_list_file;

typedef struct t_lists
{
    t_list_historic historic;
    t_list_file files;
} t_lists;
//* end of forward declaration

typedef struct t_command
{
    char *name;
    void (*func)(type_args, t_lists *);
    char *short_help;
    char *long_help;
} t_command;

#endif /* TYPES_H */