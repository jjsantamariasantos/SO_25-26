#ifndef AUXILIAR_H
#define AUXILIAR_H

#include "types.h"
#include "historic_list.h"
#include "file_list.h"
#include "commands.h"


void print_prompt();
bool read_input(t_lists *L);
void process_input(t_lists *L, bool *exit_shell);
int cut_input(char *input, char *args[]);
void select_command(type_args args, char *input ,t_lists *L, bool *exit_shell);
void free_historic_list(t_list_historic *L);
void free_file_list(t_list_file *L);
void print_error(char * name, char *msg);
void print_system_error(char * name);
int get_commands_length();
void get_commands(t_command *commands_copy);
void initialize_file_list(t_list_file *L);
bool string_to_int(char *str, int *num);

#endif /*AUXILIAR_H*/