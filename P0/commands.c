#include "commands.h"

//*auxiliary functions for commands

//*historic auxiliary functions
void print_historic(type_args args, t_list_historic *list);
void print_historic_last_n_commands(type_args args, t_list_historic *list, int n);
void print_historic_command_n(type_args args, t_list_historic *list, int n);
void clear_historic(t_list_historic *list);
void count_historic(t_list_historic *list);
//*end of historic auxiliary functions

//*open auxiliary functions
void open(type_args args, t_list_file *list);
void print_item_file(t_item_file item);
int get_mode(char *mode_str);
const char* mode_to_string(int mode);
//*end of open auxiliary functions*/

//*close auxiliary functions
void close(type_args args, t_list_file *list, int fd);
//*end of close auxiliary functions

//*dup auxiliary functions
void dup(type_args args, t_list_file *list, int fd);
//*end of dup auxiliary functions

//*listopen auxiliary functions
void open_file_list(t_list_file *list);
//*end of listopen auxiliary functions

//*help auxiliary functions
void short_help_cmds();
void long_help_cmd( type_args args);
//*end of help auxiliary functions

//*end of auxiliary functions for commands


void cmd_authors(type_args args, t_lists *lists);
void cmd_getpid(type_args args, t_lists *lists);
void cmd_chdir(type_args args, t_lists *lists);
void cmd_getcwd(type_args args, t_lists *lists);
void cmd_date(type_args args, t_lists *lists);

void cmd_historic(type_args args, t_lists *lists){
    if(args.length == 1){
        print_historic(args, &lists->historic);
    } else if(args.length == 2){
        int n;
        if(args.input[1][0] == '-'){
            if(strlen(args.input[1]) > 1){
                if(string_to_int(&args.input[1][1], &n)){
                    if(n > 0)
                        print_historic_last_n_commands(args, &lists->historic, n);
                    else
                        print_error(args.input[0], "N must be a positive integer");
                } else if(strcmp(args.input[1][2], "l") == 0)
                    clear_historic(&lists->historic);
                else if(strcmp(args.input[1][2], "o") == 0)
                    count_historic(&lists->historic);
                else
                    print_error(args.input[0], "Invalid argument");
            } else 
                print_error(args.input[0], "Invalid argument");

            return;
        } else {
            if(string_to_int(args.input[1], &n)){
                if(n > 0)
                    print_historic_command_n(args, &lists->historic, n);
                else
                    print_error(args.input[0], "N must be a positive integer");
            } else 
                print_error(args.input[0], "Invalid argument");

            return;
        }
    }
    print_error(args.input[0], "Invalid num of arguments");
}

void cmd_open(type_args args, t_lists *lists){
    if(args.length == 1)
        cmd_listopen(args, lists);
    else if(args.length < 1)
        printError(args.input[0], "Invalid argument");
    else
        open(args, &lists->files);
}

void cmd_close(type_args args, t_lists *lists){
    switch (args.length)
    {
    case 1:
        cmd_listopen(args, lists);
        break;
    case 2:
        int fd;
        if(!string_to_int(args.input[1], &fd))
            print_error(args.input[0], "Invalid argument");
        else if (fd < 0)
            print_error(args.input[0], "fd must be a non-negative integer");
        else
            close(args, &lists->files, fd);
    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}
void cmd_dup(type_args args, t_lists *lists){
    switch (args.length)
    {
    case 1: 
        cmd_listopen(args, lists);
        break;
    case 2:
        int fd;
        if(!string_to_int(args.input[1], &fd))      
            print_error(args.input[0], "Invalid argument");
        else if (fd < 0)
            print_error(args.input[0], "fd must be a non-negative integer");
        else
            dup(args, &lists->files, fd);
        break;
    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}

void cmd_listopen(type_args args, t_lists *lists){
    UNUSED(args);
    open_file_list(&lists->files);
}

void cmd_infosys(type_args args, t_lists *lists);

void cmd_help(type_args args, t_lists *lists){
    UNUSED(lists);

    switch (args.length)
    {
    case 1:
        short_help_cmds();
        break;
    case 2:
        long_help_cmd(args);
        break;
    default:
        print_error(args.input[0], "Too many arguments");
        break;
    }
}

void cmd_exit_quit_bye(type_args args, bool *exit_shell){
    if(args.length == 1){
        *exit_shell = true;
    } else {
        print_error(args.input[0], "Too many arguments");
    }
}

void short_help_cmds(){
    const int num = get_commands_length(), total = num + 3;  //* +3 for exit, quit and bye
    t_command commands[num];
    get_commands(commands);

    puts("List of available commands:");

    for(int i = 0; i < total; i++){
        if(i < num){
            printf("%10s\n", commands[i].name);
        }   else if(i == num){
            printf("%10s\n", SHORT_HELP_EXIT);
        } else if(i == num + 1){
            printf("%10s\n",  SHORT_HELP_QUIT);
        } else if(i == num + 2){
            printf("%10s\n", SHORT_HELP_BYE);
        }

        if((i + 1) % 5 == 0)
            puts("");
    }
    if((total % 5) != 0)
        puts("");
    
}

void long_help_cmd( type_args args){
    const int num = get_commands_length();
    t_command commands[num];

    get_commands(commands);

    for(int i = 0; i < num; i++){
        for(int j = 0; commands[i].name[j]; j++){
            if(strcmp(args.input[1], commands[i].name) == 0){
                printf("Usage: %s\n\n%s\n", commands[i].short_help, commands[i].long_help);
                return;
            }
        }
    }

    if(strcmp(args.input[1], "exit") == 0 ||
        strcmp(args.input[1], "quit") == 0 ||
        strcmp(args.input[1], "bye") == 0){

        printf("Usage: %s\n\n%s\n", args.input[1],LONG_HELP_EXIT_COMMANDS);
        return;
    }

    print_error(args.input[1], "Command not found");
}