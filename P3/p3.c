/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#include "auxiliar.h"

void shell_loop(args_main args_main);
int main(int argc, char *argv[], char *envp[])
{
    args_main args_main;
    args_main.argc = argc;
    args_main.argv = argv;
    args_main.envp = envp;
    shell_loop(args_main);
        
    return 0;
}

void shell_loop(args_main args_main)
{
    bool exit_shell = false;
    t_lists L;

    create_empty_list_historic(&L.historic);
    create_empty_list_file(&L.files);
    initialize_file_list(&L.files);
    create_empty_list_background(&L.background);
    create_empty_list_mem(&L.memory);
    L.dir_flags = 0;
    type_args args;
    args.args_main = args_main;
    while (!exit_shell)
    {
        print_prompt();
        if (read_input(&L))
            process_input(&L, &exit_shell, args);
    }
    free_lists(&L);   
}

