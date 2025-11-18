/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#include "commands.h"

//*auxiliary functions for commands

//*multiple commands auxiliary functions
int get_mode(type_args mode_str);
void open_dir(type_args args, char *path, unsigned char flags, 
    void function(type_args args, int n, unsigned char flags, char *full_path));
char *build_path(char *relative_path, char *full_path);
bool is_directory(type_args args, char *path);
void delete_aux(type_args args, void function(type_args args, int n, unsigned char flags, char *full_path));
//*end of multiple commands auxiliary functions

//* authors auxiliary functions
void print_login();
void print_authors();
//*end of authors auxiliary functions

//*historic auxiliary functions
void print_historic(type_args args, t_list_historic *list);
void print_historic_last_n_commands(type_args args, t_list_historic *list, int n);
void print_historic_command_n(type_args args, t_lists *list, int n);
void clear_historic(t_list_historic *list);
void count_historic(t_list_historic *list);
//*end of historic auxiliary functions

//*open auxiliary functions
void open_aux(type_args args, t_list_file *list);
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

//*create auxiliary functions
//*end of create auxiliary functions

//*setdirparams auxiliary functions
//*end of setdirparams auxiliary functions

//*getdirparams auxiliary functions
//*end of getdirparams auxiliary functions

//*dir auxiliary functions
//*end of dir auxiliary functions

//*erase auxiliary functions
void erase_aux(type_args args, int n, unsigned char flags, char *full_path);
//*end of erase auxiliary functions

//*delrec auxiliary functions
void delrec_aux(type_args args, int n, unsigned char flags, char *full_path);
//*end of delrec auxiliary functions

//*lseek auxiliary functions
int get_ref(char *ref_str);
char *ref_to_str(int ref);
void lseek_aux(type_args args, t_list_file *list, int fd, off_t offset, int ref);
//*end of lseek auxiliary functions

//*writestr auxiliary functions
void writestr_aux(type_args args, t_list_file *list, int fd, char *str);
//*end of writestr auxiliary functions

//*end of auxiliary functions for commands



/****************************************************
 *                FUNCIONES P0                      *
 ****************************************************/
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

        if (strcmp(new_args.input[0], "historic") == 0 && new_args.length == 2 &&
        args.input[1][0] != '-')
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



/****************************************************
 *                FUNCIONES P1                      *
 ****************************************************/
void open_dir(type_args args, char *path, unsigned char flags, 
    void function(type_args args, int n, unsigned char flags, char *full_path))
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        print_file_error(args.input[0], path);
        return;
    }
    type_args new_args;
    new_args.input[0] = args.input[0];
    new_args.length = 2;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (!(flags & FLAG_AVOID) || (strcmp(entry->d_name, ".") != 0 && 
        strcmp(entry->d_name, "..") != 0))
        {
            if ((flags & FLAG_HID) || entry->d_name[0] != '.')
            {
                new_args.input[1] = entry->d_name;
                function(new_args, 1, flags, path);
            }
        }
    }
    closedir(dir);
}

char *build_path(char *relative_path, char *full_path)
{
    char *new_path;
    if (full_path == NULL)
    {
        new_path = strdup(relative_path);
    }
    else
    {
        size_t length = strlen(full_path) + strlen(relative_path) + 2;
        new_path = malloc(length * sizeof(char));
        snprintf(new_path, length, "%s/%s", full_path, relative_path);
    }
    return new_path;
}

bool is_directory(type_args args, char *path)
{
    struct stat file_stat;

    if (lstat(path, &file_stat) != 0)
    {
        print_file_error(args.input[0], path);
        return false;
    }

    return S_ISDIR(file_stat.st_mode);
}

void delete_aux(type_args args, 
    void function(type_args args, int n, unsigned char flags, char *full_path))
{
    if (args.length == 1)
    {
        print_error(args.input[0], "Missing operand");
        return;
    }
    else if (args.length > 1)
    {
        for (int i = 1; i < args.length; i++)
        {
            function(args, i, 0, NULL);
        }
    }
}

void cmd_create(type_args args, t_lists *L)
{
    UNUSED(L);

    if (args.length == 1)
    {
        char cwd[MAX_INPUT_SIZE];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd);
        else
            perror("getcwd");
        return;
    }

    if (args.input[1][0] == '-' && strcmp(args.input[1], "-f") != 0)
    {
        printf("Uso: create [-f] nombre\n");
        return;
    }

    if (strcmp(args.input[1], "-f") == 0)
    {
        if (args.length < 3)
        {
            printf("Uso: create -f nombre_archivo\n");
            return;
        }

        int fd = open(args.input[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
        if (fd == -1)
        {
            print_file_error(args.input[0], args.input[2]);
            return;
        }

        close(fd);
        return;
    }

    int res = mkdir(args.input[1], 0777);
    if (res == -1)
    {
        print_file_error(args.input[0], args.input[1]);
        return;
    }
}

void cmd_setdirparams(type_args args, t_lists *L)
{
    if (args.length < 2)
    {
        printf("Uso: setdirparams [long|short] [link|nolink] [hid|nohid] [reca|recb|norec]\n");
        return;
    }

    for (int i = 1; i < args.length; i++)
    {
        char *param = args.input[i];

        for (char *p = param; *p; ++p)
            *p = tolower(*p);

        if (strcmp(param, "long") == 0)
            L->dir_flags |= FLAG_LONG;
        else if (strcmp(param, "short") == 0)
            L->dir_flags &= ~FLAG_LONG;

        else if (strcmp(param, "link") == 0)
            L->dir_flags |= FLAG_LINK;
        else if (strcmp(param, "nolink") == 0)
            L->dir_flags &= ~FLAG_LINK;

        else if (strcmp(param, "hid") == 0)
            L->dir_flags |= FLAG_HID;
        else if (strcmp(param, "nohid") == 0)
            L->dir_flags &= ~FLAG_HID;

        else if (strcmp(param, "reca") == 0)
        {
            L->dir_flags &= ~FLAG_AVOID;
            L->dir_flags |= FLAG_ACC;
        }
        else if (strcmp(param, "recb") == 0)
        {
            L->dir_flags &= ~FLAG_ACC;
            L->dir_flags |= FLAG_AVOID;
        }
        else if (strcmp(param, "norec") == 0)
            L->dir_flags &= ~(FLAG_ACC | FLAG_AVOID);

        else
            print_file_error(args.input[0], param);
    }
}

void cmd_getdirparams(type_args args, t_lists *L)
{
    UNUSED(args);

    printf("long: %s\n", (L->dir_flags & FLAG_LONG) ? "on" : "off");
    printf("link: %s\n", (L->dir_flags & FLAG_LINK) ? "on" : "off");
    printf("hid:  %s\n", (L->dir_flags & FLAG_HID) ? "on" : "off");

    if (L->dir_flags & FLAG_ACC)
        printf("recursion(despues)\n");
    else if (L->dir_flags & FLAG_AVOID)
        printf("recursion(antes)\n");
    else
        printf("recursion: norec\n");
}

static void print_file_info(type_args args, const char *path, const char *name, int flags)
{
    char full_path[MAX_INPUT_SIZE];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, name);

    struct stat st;
    if (lstat(full_path, &st) == -1)
    {
        print_file_error(args.input[0], (char *)full_path);
        return;
    }

    if (!(flags & FLAG_LONG))
    {
        printf("%-25s %10ld\n", name, (long)st.st_size);
        return;
    }

    char perms[11] = "----------";
    if (S_ISDIR(st.st_mode))
        perms[0] = 'd';
    else if (S_ISLNK(st.st_mode))
        perms[0] = 'l';
    if (st.st_mode & S_IRUSR)
        perms[1] = 'r';
    if (st.st_mode & S_IWUSR)
        perms[2] = 'w';
    if (st.st_mode & S_IXUSR)
        perms[3] = 'x';
    if (st.st_mode & S_IRGRP)
        perms[4] = 'r';
    if (st.st_mode & S_IWGRP)
        perms[5] = 'w';
    if (st.st_mode & S_IXGRP)
        perms[6] = 'x';
    if (st.st_mode & S_IROTH)
        perms[7] = 'r';
    if (st.st_mode & S_IWOTH)
        perms[8] = 'w';
    if (st.st_mode & S_IXOTH)
        perms[9] = 'x';

    struct tm *tm_info = localtime(&st.st_mtime);
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);

    printf("%s %3ld %8s %8s %8ld %s %s",
           perms, (long)st.st_nlink,
           pw ? pw->pw_name : "?", gr ? gr->gr_name : "?",
           (long)st.st_size, timebuf, name);

    if ((flags & FLAG_LINK) && S_ISLNK(st.st_mode))
    {
        char linktarget[MAX_INPUT_SIZE];
        ssize_t len = readlink(full_path, linktarget, sizeof(linktarget) - 1);
        if (len != -1)
        {
            linktarget[len] = '\0';
            printf(" -> %s", linktarget);
        }
    }

    printf("\n");
}

static void list_directory(type_args args, const char *path, int flags, bool header)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        print_file_error(args.input[0], (char *)path);
        return;
    }

    if (header)
        printf("\n%s:\n", path);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (!(flags & FLAG_HID) && entry->d_name[0] == '.')
            continue;

        print_file_info(args, path, entry->d_name, flags);
    }
    closedir(dir);
}

static void dir_recursive(type_args args, const char *path, int flags, bool before)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        print_file_error(args.input[0], (char *)path);
        return;
    }

    struct dirent *entry;

    if (before)
        list_directory(args, path, flags, true);

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (!(flags & FLAG_HID) && entry->d_name[0] == '.')
            continue;

        char new_path[MAX_INPUT_SIZE];
        snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (lstat(new_path, &st) == -1)
        {
            print_file_error(args.input[0], new_path);
            continue;
        }

        if (S_ISDIR(st.st_mode))
        {
            dir_recursive(args, new_path, flags, before);
        }
    }

    if (!before)
        list_directory(args, path, flags, true);

    closedir(dir);
}

void cmd_dir(type_args args, t_lists *L)
{
    int flags = L->dir_flags;
    bool dash_d = false;
    int start_index = 1;

    if (args.length > 1 && strcmp(args.input[1], "-d") == 0)
    {
        dash_d = true;
        start_index = 2;
    }

    if (args.length == 1 || (dash_d && args.length == 2))
    {
        char *path = ".";
        if (dash_d)
        {
            if (flags & FLAG_ACC)
                dir_recursive(args, path, flags, true);
            else if (flags & FLAG_AVOID)
                dir_recursive(args, path, flags, false);
            else
                list_directory(args, path, flags, false);
        }
        else
        {
            list_directory(args, path, flags, false);
        }
        return;
    }

    for (int i = start_index; i < args.length; i++)
    {
        char *path = args.input[i];
        struct stat st;

        if (lstat(path, &st) == -1)
        {
            print_file_error(args.input[0], path);
            continue;
        }

        if (S_ISDIR(st.st_mode))
        {
            if (dash_d)
            {
                if (flags & FLAG_ACC)
                    dir_recursive(args, path, flags, true);
                else if (flags & FLAG_AVOID)
                    dir_recursive(args, path, flags, false);
                else
                    list_directory(args, path, flags, true);
            }
            else
            {
                print_file_info(args, ".", path, flags);
            }
        }
        else
        {
            print_file_info(args, ".", path, flags);
        }
    }
}

void erase_aux(type_args args, int n, unsigned char flags, char *full_path)
{
    UNUSED(flags);
    char *path = build_path(args.input[n], full_path);

    if (remove(path) == 0)
    {
        printf("File %s erased successfully\n", path);
    }
    else
    {
        print_file_error(args.input[0], path);
    }

    free(path);
}

void cmd_erase(type_args args, t_lists *lists)
{
    UNUSED(lists);
    delete_aux(args, erase_aux);
}

void delrec_aux(type_args args, int n, unsigned char flags, char *full_path)
{
    UNUSED(flags);
    char *path = build_path(args.input[n], full_path);

    if (remove(path) == -1)
    {
        open_dir(args, path, 0, delrec_aux);
        if (remove(path) == -1)
        {
            print_file_error(args.input[0], path);
        }
        else
        {
            printf("Directory %s deleted successfully\n", path);
        }
    }
    free(path);
}

void cmd_delrec(type_args args, t_lists *lists)
{
    UNUSED(lists);
    delete_aux(args, delrec_aux);
}

int get_ref(char *ref_str)
{
    if (strcmp(ref_str, "SEEK_SET") == 0)
        return SEEK_SET;
    else if (strcmp(ref_str, "SEEK_CUR") == 0)
        return SEEK_CUR;
    else if (strcmp(ref_str, "SEEK_END") == 0)
        return SEEK_END;
    else
        return -1;
}

char *ref_to_str(int ref)
{
    switch (ref)
    {
    case SEEK_SET:
        return "SEEK_SET";
    case SEEK_CUR:
        return "SEEK_CUR";
    case SEEK_END:
        return "SEEK_END";
    default:
        return "UNKNOWN";
    }
}

void lseek_aux(type_args args, t_list_file *list, int fd, off_t offset, int ref)
{
    t_pos_file pos = find_item_file(fd, *list);

    if (pos == FNULL)
    {
        print_error(args.input[0], "Bad file descriptor");
        return;
    }

    t_item_file item = get_item_file(pos, *list);

    if (strcmp(item.file_name, "unused") == 0)
    {
        print_error(args.input[0], "File descriptor is not in use");
        return;
    }

    off_t new_offset = lseek(fd, offset, ref);

    if (new_offset == -1)
    {
        print_system_error(args.input[0]);
        return;
    }

    printf("File %s (fd %d): offset positioned at %ld using %s\n",
           item.file_name, fd, (long)new_offset, ref_to_str(ref));
}

void cmd_lseek(type_args args, t_lists *lists)
{
    int fd, ref;
    off_t offset;
    
    if(args.length > 1){
        if (!string_to_int(args.input[1], &fd))
        {
            print_error(args.input[0], "Invalid file descriptor");
            return;
        }

        if (fd < 0)
        {
            print_error(args.input[0], "fd must be a non-negative integer");
            return;
        }
        long temp_offset;
        if (!string_to_int(args.input[2], (int *)&temp_offset))
        {
            print_error(args.input[0], "Invalid offset");
            return;
        }
        offset = (off_t)temp_offset;

        ref = get_ref(args.input[3]);
        if (ref == -1)
        {
            print_error(args.input[0], "Invalid reference (use SEEK_SET, SEEK_CUR, or SEEK_END)");
            return;
        }

        lseek_aux(args, &lists->files, fd, offset, ref);
    }
    print_error(args.input[0], "Incorrect parameters");
    


}
void writestr_aux(type_args args, t_list_file *list, int fd, char *str)
{
    t_pos_file pos = find_item_file(fd, *list);

    if (pos == FNULL)
    {
        print_error(args.input[0], "Bad file descriptor");
        return;
    }

    t_item_file item = get_item_file(pos, *list);

    if (strcmp(item.file_name, "unused") == 0)
    {
        print_error(args.input[0], "File descriptor is not in use");
        return;
    }

    ssize_t bytes_written = write(fd, str, strlen(str));

    if (bytes_written == -1)
    {
        print_system_error(args.input[0]);
        return;
    }

    printf("Wrote %zd bytes to file %s (fd %d)\n", bytes_written, item.file_name, fd);
}

void cmd_writestr(type_args args, t_lists *lists)
{
    int fd;

    if (!string_to_int(args.input[1], &fd))
    {
        print_error(args.input[0], "Invalid file descriptor");
        return;
    }

    if (fd < 0)
    {
        print_error(args.input[0], "fd must be a non-negative integer");
        return;
    }

    char *str = args.input[2];

    writestr_aux(args, &lists->files, fd, str);
}



/****************************************************
 *                FUNCIONES P2                      *
 ****************************************************/

void cmd_malloc(type_args args, t_lists *lists){

}
void cmd_mmap(type_args args, t_lists *lists){

}
void cmd_shared(type_args args, t_lists *lists){

}
void cmd_free(type_args args, t_lists *lists){
    
}
void cmd_memfill(type_args args, t_lists *lists){

}
void cmd_memdump(type_args args, t_lists *lists){

}
void cmd_mem(type_args args, t_lists *lists){

}
void cmd_readfile(type_args args, t_lists *lists){

}
void cmd_writefile(type_args args, t_lists *lists){

}
void cmd_read(type_args args, t_lists *lists){

}
void cmd_write(type_args args, t_lists *lists){

}
void cmd_recurse(type_args args, t_lists *lists){
    
}