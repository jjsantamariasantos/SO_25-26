
#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/utsname.h>

#define MAX_INPUT_SIZE 1024
#define SNULL -1
#define UNUSED(f) do { (void)(f); } while (0) // to avoid warnings of unused variables
#define ARGS_MAX 10

typedef struct type_args{
    char *input[ARGS_MAX];
    int length;
} type_args;

// forward declaration for list
typedef struct t_node *t_pos_historic;
typedef t_pos_historic t_list_historic;  

typedef struct t_node *t_pos_file;
typedef t_pos_file t_list_file;

typedef struct t_lists{
    t_list_historic historic;
    t_list_file file;
}t_lists;
// end of forward declaration

typedef struct t_command{
    char *name;
    void (*func)(type_args, t_lists*);
    char *short_help;
    char *long_help;
}t_command;

#endif  /* MACROS_H */