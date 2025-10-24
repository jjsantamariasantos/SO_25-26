#include "commands.h"

//*auxiliary functions for commands

//* authors auxiliary functions
void print_login();
void print_authors();
//*end of authors auxiliary functions

//* date auxili

//*historic auxiliary functions
void print_historic(type_args args, t_list_historic *list);
void print_historic_last_n_commands(type_args args, t_list_historic *list, int n);
void print_historic_command_n(type_args args, t_lists *list, int n);
void clear_historic(t_list_historic *list);
void count_historic(t_list_historic *list);
//*end of historic auxiliary functions

//*open auxiliary functions
void open_aux(type_args args, t_list_file *list);
int get_mode(type_args mode_str); //* used to in list_open
const char *mode_to_string(int mode);
//*end of open auxiliary functions*/

//*close auxiliary functions
void close_aux(type_args args, t_list_file *list, int fd);
//*end of close auxiliary functions

//*dup auxiliary functions
void dup_aux(type_args args, t_list_file *list, int fd);
//*end of dup auxiliary functions

//*list_open auxiliary functions
void open_file_list(t_list_file *list);
void print_item_file(t_item_file item);
//*end of list_open auxiliary functions

//*help auxiliary functions
void short_help_cmds();
void long_help_cmd(type_args args);
//*end of help auxiliary functions

//*end of auxiliary functions for commands

void cmd_authors(type_args args, t_lists *lists)
{
    UNUSED(lists);
    switch (args.length)
    {
    case 1:
        print_authors();
        print_login();
        break;
    case 2:
        if (strcmp(args.input[1], "-l") == 0)
            print_login();
        else if (strcmp(args.input[1], "-n") == 0)
            print_authors();
        else
            print_error(args.input[1], "Invalid argument");

        break;
    case 3:
        if (((strcmp(args.input[1], "-l") == 0) && (strcmp(args.input[2], "-n") == 0)) ||
            ((strcmp(args.input[1], "-n") == 0) && (strcmp(args.input[2], "-l") == 0)))
        {
            print_authors();
            print_login();
        }
        else
            print_error(args.input[0], "Invalid argument");

        break;
    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}

void cmd_getpid(type_args args, t_lists *lists)
{
    UNUSED(lists);
    switch (args.length)
    {
    case 1: // solo "getpid"
        printf("PID: %d\n", getpid());
        break;
    case 2: // getpid -p
        if (strcmp(args.input[1], "-p") == 0)
            printf("Parent PID: %d\n", getppid());
        else
            print_error(args.input[0], "Invalid argument");

        break;
    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}

void cmd_getcwd(type_args args, t_lists *lists)
{
    char cwd[1024];
    UNUSED(lists);
    if (args.length == 1)
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("Directorio actual: \033[1;34m%s\033[0m\n", cwd);
        }
        else
        {
            perror("\033[31mgetcwd() error\033[0m");
        }
    }
    else
        print_error(args.input[0], "Invalid num of arguments");
}

void cmd_chdir(type_args args, t_lists *lists)
{

    UNUSED(lists);
    switch (args.length)
    {
    case 1:
        cmd_getcwd(args, lists);
        break;

    case 2: // chdir <dir>
        if (chdir(args.input[1]) != 0)
        {
            perror("\033[31mchdir() error\033[0m");
        }
        else
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            printf("Exitoso cambio a \033[1;34m%s\033[0m\n", cwd);
        }
        break;

    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}

void cmd_date(type_args args, t_lists *lists)
{
    time_t now;
    time(&now);
    UNUSED(lists);
    struct tm *local = localtime(&now);

    switch (args.length)
    {
    case 1:
        printf("Dia:\n    %02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
        printf("Hora:\n    %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
        break;

    case 2:
        if (strcmp(args.input[1], "-d") == 0)
            printf("Dia:\n    %02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
        else if (strcmp(args.input[1], "-t") == 0)
            printf("Hora:\n    %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
        else
            print_error(args.input[1], "Invalid argument");

        break;
    case 3:
        if (((strcmp(args.input[1], "-d") == 0) && (strcmp(args.input[2], "-t") == 0)) ||
            ((strcmp(args.input[1], "-t") == 0) && (strcmp(args.input[2], "-d") == 0)))
        {
            printf("Dia:\n    %02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
            printf("Hora:\n    %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
        }
        else
            print_error(args.input[0], "Invalid argument");

        break;
    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}

void cmd_historic(type_args args, t_lists *lists)
{
    switch (args.length)
    {
    case 1:
        print_historic(args, &lists->historic);
        break;
    case 2:
        int n;

        if (args.input[1][0] == '-')
        {
            if (strlen(args.input[1]) > 1)
            {
                if (string_to_int(&args.input[1][1], &n))
                {
                    if (n > 0)
                        print_historic_last_n_commands(args, &lists->historic, n);
                    else
                        print_error(args.input[1] + 1, "N must be a positive integer");
                }
                else if (strcmp(args.input[1], "-clear") == 0)
                    clear_historic(&lists->historic);
                else if (strcmp(args.input[1], "-count") == 0)
                    count_historic(&lists->historic);
                else
                    print_error(args.input[0], "Invalid argument");
            }
            else
                print_error(args.input[0], "Invalid argument");
            break;
        }
        else
        {
            if (string_to_int(args.input[1], &n))
            {
                if (n > 0)
                    print_historic_command_n(args, lists, n);
                else
                    print_error(args.input[0], "N must be a positive integer");
            }
            else
                print_error(args.input[0], "Invalid argument");
            break;
        }
    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}

void cmd_open(type_args args, t_lists *lists)
{
    if (args.length == 1)
        cmd_list_open(args, lists);
    else if (args.length < 1)
        print_error(args.input[0], "Invalid argument");
    else
        open_aux(args, &lists->files);
}

void cmd_close(type_args args, t_lists *lists)
{
    switch (args.length)
    {
    case 1:
        cmd_list_open(args, lists);
        break;
    case 2:
        int fd;
        if (!string_to_int(args.input[1], &fd))
            print_error(args.input[0], "Invalid argument");
        else if (fd < 0)
            print_error(args.input[0], "fd must be a non-negative integer");
        else
            close_aux(args, &lists->files, fd);
        break;
    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}
void cmd_dup(type_args args, t_lists *lists)
{
    switch (args.length)
    {
    case 1:
        cmd_list_open(args, lists);
        break;
    case 2:
        int fd;
        if (!string_to_int(args.input[1], &fd))
            print_error(args.input[0], "Invalid argument");
        else if (fd < 0)
            print_error(args.input[0], "fd must be a non-negative integer");
        else
            dup_aux(args, &lists->files, fd);
        break;
    default:
        print_error(args.input[0], "Invalid num of arguments");
        break;
    }
}

void cmd_list_open(type_args args, t_lists *lists)
{
    UNUSED(args);
    open_file_list(&lists->files);
}

void cmd_infosys(type_args args, t_lists *lists)
{
    UNUSED(args);
    UNUSED(lists);
    struct utsname buffer;

    if (uname(&buffer) != 0)
    {
        perror("uname failed");
        return;
    }

    printf("System Information:\n");
    printf("    Node Name:   %s\n", buffer.nodename);
    printf("    System Name: %s\n", buffer.sysname);
    printf("    Release:     %s\n", buffer.release);
    printf("    Version:     %s\n", buffer.version);
    printf("    Machine:     %s\n", buffer.machine);
}

void cmd_help(type_args args, t_lists *lists)
{
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

void cmd_exit_quit_bye(type_args args, bool *exit_shell)
{
    if (args.length == 1)
        *exit_shell = true;
    else
        print_error(args.input[0], "Too many arguments");
}

void print_historic(type_args args, t_list_historic *list)
{
    t_item_historic item;
    int i = 1;

    if (!is_empty_list_historic(*list))
    {
        t_pos_historic pos = first_position_historic(*list);
        while (pos != HNULL)
        {
            item = get_item_historic(pos, *list);
            printf("%d: %s\n", i, item.command);
            pos = next_position_historic(pos, *list);
            i++;
        }
    }
    else
        print_error(args.input[0], "Historic is empty");
}
void print_authors()
{
    puts(AUTHOR_NAME_1);
    puts(AUTHOR_NAME_2);
}

void print_login()
{
    puts(AUTHOR_LOGIN_1);
    puts(AUTHOR_LOGIN_2);
}
void print_historic_last_n_commands(type_args args, t_list_historic *list, int n)
{
    t_item_historic item;
    t_pos_historic pos;
    int i = 1;

    if (n > 0)
    {
        if (!is_empty_list_historic(*list))
        {
            pos = last_position_historic(*list);

            for (; i < n; i++)
            {
                if (pos != HNULL)
                    pos = previous_position_historic(pos, *list);
                else
                {
                    pos = first_position_historic(*list);
                    break;
                }
            }
            for (; pos != HNULL; pos = next_position_historic(pos, *list))
            {
                item = get_item_historic(pos, *list);
                printf("%d: %s\n", item.num_command, item.command);
            }
        }
        else
            print_error(args.input[0], "Historic is empty");
    }
    else
        print_error(args.input[0], "Invalid argument");
}

void print_historic_command_n(type_args args, t_lists *list, int n)
{
    if (!is_empty_list_historic(list->historic))
    {
        t_pos_historic pos = first_position_historic(list->historic);
        t_item_historic item = get_item_historic(pos, list->historic);

        for (; pos != HNULL; pos = next_position_historic(pos, list->historic))
        {
            if (item.num_command == n)
                break;

            item = get_item_historic(pos, list->historic);
        }

        if (pos == HNULL)
        {
            print_error(args.input[0], "Command number not found");
            return;
        }

        type_args new_args;
        new_args.length = cut_input(item.command, new_args.input);

        if (strcmp(new_args.input[0], "historic") == 0 && new_args.length == 2 && args.input[1][0] != '-')
        {
            print_error(args.input[0], "Avoid infinite looping");
            return;
        }
        select_command(new_args, item.command, list, false);
    }
    else
        print_error(args.input[0], "Historic is empty");
}

void clear_historic(t_list_historic *list)
{
    if (!is_empty_list_historic(*list))
    {
        free_historic_list(list);
        create_empty_list_historic(list);
    }
    else
        print_error("historic", "Historic is already empty");
}

void count_historic(t_list_historic *list)
{
    int count = 0;

    if (!is_empty_list_historic(*list))
    {
        t_pos_historic pos = first_position_historic(*list);
        for (; pos != HNULL; pos = next_position_historic(pos, *list))
            count++;
    }
    printf("Number of commands in historic: %d\n", count);
}

void open_aux(type_args args, t_list_file *list)
{
    int fd, mode;
    t_item_file item;
    t_pos_file pos;

    mode = get_mode(args);

    if ((fd = open(args.input[1], mode, 0777)) == -1)
        print_system_error(args.input[0]);
    else
    {
        item.fd = fd;

        strcpy(item.file_name, args.input[1]);
        item.mode = mode;
        pos = find_item_file(fd, *list);

        if (pos == FNULL)
        {
            if (!insert_item_file(item, pos, list))
            {
                print_error(args.input[0], "Error inserting file into list");
                if (close(fd) == -1)
                    print_system_error(args.input[0]);

                return;
            }
        }
        else
        {
            printf("a");
            update_item_file(item, pos, list);
        }

        printf("File %s opened with fd %d and mode %s\n",
               item.file_name, item.fd, mode_to_string(item.mode));
    }
}

int get_mode(type_args mode_str)
{
    int mode = 0;

    for (int i = 2; i < mode_str.length; i++)
    {
        if (strcmp(mode_str.input[i], "cr") == 0)
            mode |= O_CREAT;
        else if (strcmp(mode_str.input[i], "ap") == 0)
            mode |= O_APPEND;
        else if (strcmp(mode_str.input[i], "ex") == 0)
            mode |= O_EXCL;
        else if (strcmp(mode_str.input[i], "ro") == 0)
            mode |= O_RDONLY;
        else if (strcmp(mode_str.input[i], "rw") == 0)
            mode |= O_RDWR;
        else if (strcmp(mode_str.input[i], "wo") == 0)
            mode |= O_WRONLY;
        else if (strcmp(mode_str.input[i], "tr") == 0)
            mode |= O_TRUNC;
        else
            break;
    }

    return mode;
}

const char *mode_to_string(int mode)
{
    static char mode_str[64] = {0};
    mode_str[0] = '\0';

    if (mode & O_CREAT)
        strcat(mode_str, "O_CREAT ");
    if (mode & O_APPEND)
        strcat(mode_str, "O_APPEND ");
    if (mode & O_EXCL)
        strcat(mode_str, "O_EXCL ");
    if (mode & O_RDONLY)
        strcat(mode_str, "O_RDONLY ");
    if (mode & O_RDWR)
        strcat(mode_str, "O_RDWR ");
    if (mode & O_WRONLY)
        strcat(mode_str, "O_WRONLY ");
    if (mode & O_TRUNC)
        strcat(mode_str, "O_TRUNC ");

    int length = strlen(mode_str);

    if (length > 0)
        mode_str[length - 1] = '\0'; //* remove trailing space if buffer not empty

    return mode_str;
}

void close_aux(type_args args, t_list_file *list, int fd)
{
    if (close(fd) == -1)
        print_system_error(args.input[0]);
    else
    {
        t_item_file item;
        t_pos_file pos = find_item_file(fd, *list);

        if (pos != FNULL)
        {
            if (fd <= 9)
            {
                item = get_item_file(pos, *list);
                strcpy(item.file_name, "unused");
                item.mode = SNULL;
                update_item_file(item, pos, list);
            }
            else
            {
                delete_at_position_file(pos, list);
            }
        }
        else
            print_error(args.input[0], "Bad file descriptor");
    }
}

void dup_aux(type_args args, t_list_file *list, int fd)
{
    t_pos_file pos;
    char new_name[MAX_INPUT_SIZE + 9];
    int new_fd;

    if ((new_fd = dup(fd)) == -1)
    {
        printf("%d\n", new_fd);
        print_system_error(args.input[0]);
        return;
    }
    pos = find_item_file(fd, *list);

    if (pos != FNULL)
    {
        t_item_file item, new_item;
        item = get_item_file(pos, *list);

        printf("%s [dup] %d (%s)", new_name, fd, item.file_name);

        new_item.fd = new_fd;
        strcpy(new_item.file_name, new_name);

        pos = find_item_file(new_fd, *list);
        if (pos == FNULL)
        {
            if (!insert_item_file(new_item, FNULL, list))
            {
                print_error(args.input[0], "Error inserting file into list");
                if (close(new_fd) == -1)
                    print_system_error(args.input[0]);

                return;
            }
        }
        else
            update_item_file(new_item, pos, list);
    }
    else
        print_error(args.input[0], "Bad file descriptor");
}

void open_file_list(t_list_file *list)
{
    if (!is_empty_list_file(*list))
    {
        t_pos_file pos = first_file(*list);
        t_item_file item;

        while (pos != FNULL)
        {
            item = get_item_file(pos, *list);
            print_item_file(item);
            pos = next_file(pos, *list);
        }
    }
    else
        print_error("list_open", "File list is empty");
}

void print_item_file(t_item_file item)
{
    if (item.mode == SNULL)
        printf("descriptor: %d -> \033[1;35m%s\033[0m\n",
               item.fd, item.file_name);
    else if (strcmp(item.file_name, "unused") != 0)
    {
        printf("descriptor: %d -> \033[1;35m%s\033[0m\033[1;32m%s\033[0m\n",
               item.fd, item.file_name, mode_to_string(item.mode));
    }
    else
        printf("descriptor: %d -> \033[1;35m%10s\033[0m\n", item.fd, item.file_name);
}

void short_help_cmds()
{
    const int num = get_commands_length(), total = num + 3; //* +3 for exit, quit and bye

    t_command commands[num];
    get_commands(commands);

    puts("List of available commands:");

    for (int i = 0; i < total; i++)
    {
        if (i < num)
        {
            printf("%10s\n", commands[i].name);
        }
        else if (i == num)
        {
            printf("%10s\n", SHORT_HELP_EXIT);
        }
        else if (i == num + 1)
        {
            printf("%10s\n", SHORT_HELP_QUIT);
        }
        else if (i == num + 2)
        {
            printf("%10s\n", SHORT_HELP_BYE);
        }

        if ((i + 1) % 5 == 0)
            puts("");
    }
    if ((total % 5) != 0)
        puts("");
}

void long_help_cmd(type_args args)
{
    const int num = get_commands_length();
    t_command commands[num];

    get_commands(commands);

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; commands[i].name[j]; j++)
        {
            if (strcmp(args.input[1], commands[i].name) == 0)
            {
                printf("Usage: %s\n%s\n", commands[i].short_help, commands[i].long_help);
                return;
            }
        }
    }

    if (strcmp(args.input[1], "exit") == 0 ||
        strcmp(args.input[1], "quit") == 0 ||
        strcmp(args.input[1], "bye") == 0)
    {

        printf("Usage: %s\n\n%s\n", args.input[1], LONG_HELP_EXIT_COMMANDS);
        return;
    }

    print_error(args.input[1], "Command not found");
}
