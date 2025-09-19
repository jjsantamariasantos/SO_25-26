#ifndef COMANNDS_H
#define COMANNDS_H
#include "types.h"
#include "historic_list.h"
#include "file_list.h"

void cmd_authors(type_args args, t_lists *lists);
void cmd_getpid(type_args args, t_lists *lists);
void cmd_chdir(type_args args, t_lists *lists);
void cmd_getcwd(type_args args, t_lists *lists);
void cmd_date(type_args args, t_lists *lists);
void cmd_historic(type_args args, t_lists *lists);
void cmd_open(type_args args, t_lists *lists);
void cmd_close(type_args args, t_lists *lists);
void cmd_dup(type_args args, t_lists *lists);
void cmd_listopen(type_args args, t_lists *lists);
void cmd_infosys(type_args args, t_lists *lists);
void cmd_help(type_args args, t_lists *lists);
void cmd_exit_quit_bye(type_args args, bool *exit_shell);

#endif /*COMANNDS_H*/