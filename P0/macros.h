
#ifndef MACROS_H
#define MACROS_H

#define PROMPT "P0:~$ "

//* macros for general use
#define MAX_INPUT_SIZE 1024
#define SNULL -1
#define ARGS_MAX 10
#define PREDEFINED_DF 10
#define UNUSED(f)  \
    do             \
    {              \
        (void)(f); \
    } while (0) //* to avoid warnings of unused variables
//* end of macros for general use

//* macros for authors command
#define AUTHOR_NAME_1 "Jesús José Santamaría Santos"
#define AUTHOR_LOGIN_1 "j.j.ssantos@udc.es"
#define AUTHOR_NAME_2 "José Comerón Lado"
#define AUTHOR_LOGIN_2 "jose.comeronl@udc.es"
//* end of macros for authors command

//*macros for help texts
#define SHORT_HELP_AUTHORS "authors [-l][-n]"
#define LONG_HELP_AUTHORS "Prints the names and logins of the program authors.\n\
authors [-l] \n\
Prints only the logins. \n\
authors -[n] \n\
Prints only the names."
#define SHORT_HELP_GETPID "getpid [-p]"
#define LONG_HELP_GETPID "Prints the PID of the current process.\n\
getpid [-p] \n\
Prints the PID of the parent process."
#define SHORT_HELP_CHDIR "chdir [dir]"
#define LONG_HELP_CHDIR "Prints the current working directory.\n\
chdir [dir] \n\
Changes the current working directory to 'dir'."
#define SHORT_HELP_GETCWD "getcwd"
#define LONG_HELP_GETCWD "Prints the current working directory."
#define SHORT_HELP_DATE "date [-t][-d]"
#define LONG_HELP_DATE "Prints the current date and time.\n\
date [-t] \n\
Prints the current time in format hh:mm:ss\n\
date [-d] \n\
Prints the current date in format DD/MM/YYYY"
#define SHORT_HELP_HISTORIC "historic [N |-N | -clear | -count]"
#define LONG_HELP_HISTORIC "Shows the historic of commands executed by this shell. \n\
historic N \n\
Repeats command number N. \n\
historic -N \n\
Prints only the last N commands.\n\
historic -clear \n\
Clears the historic.\n\
historic -count \n\
Prints the number of commands in the historic."
#define SHORT_HELP_OPEN "open [file] mode"
#define LONG_HELP_OPEN "Lists the shell open files.\n\
open [file] mode\n\
Opens a file and adds it the to the list of shell open files. \n\
modes:\n\
cr: O_CREAT\t ap: O_APPEND\t ex: O_EXCL\t ro: O_RDONLY\n\
rw: O_RDWR\t wo: O_WRONLY\t tr: O_TRUNC"
#define SHORT_HELP_CLOSE "close [fd]"
#define LONG_HELP_CLOSE "Closes the df file descriptor and eliminates the corresponding item from the list"
#define SHORT_HELP_DUP "dup [fd]"
#define LONG_HELP_DUP "Duplicates the df file descriptor creating the corresponding new entry on the file list"
#define SHORT_HELP_LISTOPEN "listopen"
#define LONG_HELP_LISTOPEN "Lists the shell open files."
#define SHORT_HELP_INFOSYS "infosys"
#define LONG_HELP_INFOSYS "Prints information on the machine running the shell."
#define SHORT_HELP_HELP "help [cmd]"
#define LONG_HELP_HELP "Displays a list of available commands.\n\
help [cmd]\n\
Gives a brief help on the usage of comand cmd."
#define SHORT_HELP_QUIT "quit"
#define SHORT_HELP_EXIT "exit"
#define SHORT_HELP_BYE "bye"
#define LONG_HELP_EXIT_COMMANDS "Ends the shell."
//*end of macros for help texts

#endif /* MACROS_H */