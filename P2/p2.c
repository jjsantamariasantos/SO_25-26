/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#include "auxiliar.h"

void shell_loop();

int main(int argc, char *argv[], char *envp[])
{
    UNUSED(argc);
    UNUSED(argv);
    UNUSED(envp);

    shell_loop();

    return 0;
}

void shell_loop()
{
    bool exit_shell = false;
    t_lists L;

    create_empty_list_historic(&L.historic);
    create_empty_list_file(&L.files);
    initialize_file_list(&L.files);
    create_empty_list_mem(&L.memory);
    L.dir_flags = 0;

    while (!exit_shell)
    {
        print_prompt();
        if (read_input(&L))
            process_input(&L, &exit_shell);
    }
    free_lists(&L);   
}