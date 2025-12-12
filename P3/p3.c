/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#include "auxiliar.h"

void shell_loop(args_main args_main);
void import_path(t_list_path *path_list, args_main args_main);

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
    create_empty_list_mem(&L.memory);
    L.dir_flags = 0;
    import_path(&L.path, args_main);
    while (!exit_shell)
    {
        print_prompt();
        if (read_input(&L))
            process_input(&L, &exit_shell);
    }
    free_lists(&L);   
}

void import_path(t_list_path *path_list, args_main args_main)
{
    if(args_main.argv[1] != NULL){
        if((args_main.argv[1][0] == '-') && (args_main.argv[1][1] == 'p')){
            search_path(path_list);
            printf("\033[33m]PATH\033[0m added\n)");
            return;
        }
    }
    printf("\033[33mPATH\033[0m not imported\n"
            "Run with \033[33m-p\033[0m to import it\n");
}

