#include "auxiliar.h"

t_command commands[]=
{
    {"authors", cmd_authors, SHORT_HELP_AUTHORS, LONG_HELP_AUTHORS},
    {"getpid", cmd_getpid, SHORT_HELP_GETPID, LONG_HELP_GETPID},
    {"chdir", cmd_chdir, SHORT_HELP_CHDIR, LONG_HELP_CHDIR},
    {"getcwd", cmd_getcwd, SHORT_HELP_GETCWD, LONG_HELP_GETCWD},
    {"date", cmd_date, SHORT_HELP_DATE, LONG_HELP_DATE},
    {"historic", cmd_historic, SHORT_HELP_HISTORIC, LONG_HELP_HISTORIC},
    {"open", cmd_open, SHORT_HELP_OPEN, LONG_HELP_OPEN},
    {"close", cmd_close, SHORT_HELP_CLOSE, LONG_HELP_CLOSE},
    {"dup", cmd_dup, SHORT_HELP_DUP, LONG_HELP_DUP},
    {"listopen", cmd_listopen, SHORT_HELP_LISTOPEN, LONG_HELP_LISTOPEN},
    {"infosys", cmd_infosys, SHORT_HELP_INFOSYS, LONG_HELP_INFOSYS},
    {"help", cmd_help, SHORT_HELP_HELP, LONG_HELP_HELP},
    {"quit", cmd_exit_quit_bye, SHORT_HELP_QUIT, LONG_HELP_EXIT_COMMANDS},
    {"exit", cmd_exit_quit_bye, SHORT_HELP_EXIT, LONG_HELP_EXIT_COMMANDS},
    {"bye", cmd_exit_quit_bye, SHORT_HELP_BYE, LONG_HELP_EXIT_COMMANDS},
    {NULL, NULL, NULL, NULL}
};
int get_input(char * input){
    int length, tab;

    if(fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
        perror("Error reading input");
    
    tab = strspn(input, " \t");

    if(tab > 0){
        memmove(input, input + tab, strlen(input) - tab + 1); //* overwrite the tabs moving the characters to the left
    }

    length = strlen(input);

    if(length > 0 && input[length - 1] == '\n'){
        input[length - 1] = '\0';
        length--;
    }

    return length;
}

void print_prompt(){
    printf(PROMPT);
    fflush(stdout);
}

bool read_input(t_lists *L){
    char input[MAX_INPUT_SIZE];
    int length;
    t_item_historic new_item;

    length = get_input(input);

    if(length > 0){
        strcpy(new_item.command, input);

        if(is_empty_list_historic(L->historic)) 
            new_item.num_command = 1;
        else{
            t_pos_historic pos = last_position_historic(L->historic);
            t_item_historic last_item = get_item_historic(pos, L->historic);
            new_item.num_command = last_item.num_command + 1;
        }
        if(!insert_item_historic(new_item, HNULL, &L->historic)){
            print_error("read_input", "Error inserting command into historic list");
            return false;
        }

        return true;
    }

    return false;
}

void process_input(t_lists *L, bool *exit_shell){
   if(!is_empty_list_historic(L->historic)){
        t_item_historic last_item = get_item_historic(last_position_historic(L->historic), L->historic);
        type_args args;
        args.length = cut_input(last_item.command, args.input);
        select_command(args, last_item.command, L, exit_shell);
   }
}
