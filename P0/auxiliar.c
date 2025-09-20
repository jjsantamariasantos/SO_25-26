#include "auxiliar.h"

t_command commands[] =
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
        {"listopen", cmd_list_open, SHORT_HELP_LISTOPEN, LONG_HELP_LISTOPEN},
        {"infosys", cmd_infosys, SHORT_HELP_INFOSYS, LONG_HELP_INFOSYS},
        {"help", cmd_help, SHORT_HELP_HELP, LONG_HELP_HELP},
        {NULL, NULL, NULL, NULL}};
//*auxiliary functions
int get_input(char *input);
//*end of auxiliary functions

void print_prompt()
{
    printf(PROMPT);
}

bool read_input(t_lists *L)
{
    char input[MAX_INPUT_SIZE];
    int length;
    t_item_historic new_item;

    length = get_input(input);

    if (length > 1)
    {
        strcpy(new_item.command, input);

        if (is_empty_list_historic(L->historic))
            new_item.num_command = 1;
        else
        {
            t_pos_historic pos = last_position_historic(L->historic);
            t_item_historic last_item = get_item_historic(pos, L->historic);
            new_item.num_command = last_item.num_command + 1;
        }
        if (!insert_item_historic(new_item, HNULL, &L->historic))
        {
            print_error("read_input", "Error inserting command into historic list");
            return false;
        }

        return true;
    }

    return false;
}

void process_input(t_lists *L, bool *exit_shell)
{
    if (!is_empty_list_historic(L->historic))
    {
        t_item_historic last_item = get_item_historic(last_position_historic(L->historic), L->historic);
        type_args args;
        args.length = cut_input(last_item.command, args.input);
        select_command(args, last_item.command, L, exit_shell);
    }
}

int cut_input(char *input, char *args[])
{
    int i = 1;

    if ((args[0] = strtok(input, " \n\t")) == NULL)
        return 0;

    while ((args[i] = strtok(NULL, " \n\t")) != NULL)
        i++;

    return i;
}

void select_command(type_args args, char *input, t_lists *L, bool *exit_shell)
{
    const int n_commands = get_commands_length();

    if (args.length > 0)
    {
        if (strcmp(args.input[0], "exit") == 0 || strcmp(args.input[0], "quit") == 0 || strcmp(args.input[0], "bye") == 0)
        {
            cmd_exit_quit_bye(args, exit_shell);
            return;
        }
        for (int i = 0; i < n_commands; i++)
        {
            if (strcmp(args.input[0], commands[i].name) == 0)
            {
                commands[i].func(args, L);
                return;
            }
        }
        print_error(input, "Command not found");
    }
}

void free_historic_list(t_list_historic *L)
{
    t_pos_historic aux;

    while (!is_empty_list_historic(*L))
    {
        aux = last_position_historic(*L);
        delete_at_position_historic(aux, L);
    }
}

void free_file_list(t_list_file *L)
{
    t_pos_file aux;

    while (!is_empty_list_file(*L))
    {
        aux = last_file(*L);
        delete_at_position_file(aux, L);
    }
}

void print_error(char *name, char *msg)
{
    fprintf(stderr, "Error: %s: %s\n", name, msg);
}

void print_system_error(char *name)
{
    fprintf(stderr, "Error: %s: %s\n", name, strerror(errno));
}

int get_commands_length()
{
    return sizeof(commands) / sizeof(t_command) - 1; //* -1 because the last element is NULL
}

void get_commands(t_command *commands_copy)
{
    int n_commands = get_commands_length();

    for (int i = 0; i < n_commands; i++)
    {
        commands_copy[i] = commands[i];
    }
}

void initialize_file_list(t_list_file *L)
{
    t_item_file input, output, error, empty;

    input.fd = 0;
    strcpy(input.file_name, "stdin");
    input.mode = O_RDWR;

    output.fd = 1;
    strcpy(output.file_name, "stdout");
    output.mode = O_RDWR;

    error.fd = 2;
    strcpy(error.file_name, "stderr");
    error.mode = O_RDWR;

    insert_item_file(input, FNULL, L);
    insert_item_file(output, FNULL, L);
    insert_item_file(error, FNULL, L);

    strcpy(empty.file_name, "unused");
    empty.mode = SNULL;

    for (int i = 3; i < PREDEFINED_DF; i++)
    {
        empty.fd = i;
        insert_item_file(empty, FNULL, L);
    }
}

bool string_to_int(char *str, int *num)
{

    char *endptr = NULL;

    *num = (int)strtol(str, &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    return true;
}

int get_input(char *input)
{
    int length, tab;

    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
        perror("Error reading input");

    tab = strspn(input, " \t");

    if (tab > 0)
    {
        memmove(input, input + tab, strlen(input) - tab + 1); //* overwrite the tabs moving the characters to the left
    }

    length = strlen(input);

    if (length > 0 && input[length - 1] == '\n')
    {
        input[length - 1] = '\0';
        length--;
    }

    return length;
}