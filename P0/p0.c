#include "auxiliar.h"

void shell_loop();

int main(int argc, char *argv[], char *envp[]){
    UNUSED(argc);
    UNUSED(argv);
    UNUSED(envp);

    shell_loop();

    return 0;
}

void shell_loop(){
    char input[MAX_INPUT_SIZE];
    bool exit_shell = false;
    t_lists L;

    initialize_lists(&L);

    while(!exit_shell){
        print_prompt();
        if(read_input(&L))
            process_input(&L, &exit_shell);
    }

    free_historic_list(&L.historic);    
    free_file_list(&L.files);
}