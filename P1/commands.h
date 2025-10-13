/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#ifndef COMANNDS_H
#define COMANNDS_H

#include "types.h"
#include "historic_list.h"
#include "file_list.h"
#include "auxiliar.h"

void cmd_authors(type_args args, t_lists *lists);
void cmd_getpid(type_args args, t_lists *lists);
void cmd_chdir(type_args args, t_lists *lists);
void cmd_getcwd(type_args args, t_lists *lists);
void cmd_date(type_args args, t_lists *lists);
void cmd_historic(type_args args, t_lists *lists);
void cmd_open(type_args args, t_lists *lists);
void cmd_close(type_args args, t_lists *lists);
void cmd_dup(type_args args, t_lists *lists);
void cmd_list_open(type_args args, t_lists *lists);
void cmd_infosys(type_args args, t_lists *lists);
void cmd_help(type_args args, t_lists *lists);
void cmd_exit_quit_bye(type_args args, bool *exit_shell);

void cmd_create(type_args args, t_lists *lists);
void cmd_setdirparams(type_args args, t_lists *lists);
void cmd_getdirparams(type_args args, t_lists *lists);
void cmd_dir(type_args args, t_lists *lists);
void cmd_erase(type_args args, t_lists *lists);
void cmd_delrec(type_args args, t_lists *lists);
void cmd_lseek(type_args args, t_lists *lists);
void cmd_writestr(type_args args, t_lists *lists);
#endif /*COMANNDS_H*/