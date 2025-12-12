/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#ifndef TYPES_H
#define TYPES_H

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "macros.h"

typedef struct args_main{
    int argc;
    char **argv, **envp;
}args_main;


typedef struct type_args
{
    char *input[ARGS_MAX];
    int length;
    args_main args_main;
} type_args;

typedef struct t_progspec{
    char **argv;
    int prio;
    bool background;
} t_progspec;

//* forward declaration for list
typedef struct t_node_historic *t_pos_historic;
typedef t_pos_historic t_list_historic;

typedef struct t_node_file *t_pos_file;
typedef t_pos_file t_list_file;

typedef struct t_node_mem *t_pos_mem;
typedef t_pos_mem t_list_mem;

typedef struct t_node_background *t_pos_background;
typedef t_pos_background t_list_background;

typedef struct t_node_path *t_pos_path;
typedef t_pos_path t_list_path;

typedef struct t_lists
{
    t_list_historic historic;
    t_list_file files;
    t_list_mem memory;
    t_list_background background;
    t_list_path path;
    unsigned char dir_flags;
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
