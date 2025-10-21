/*
authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
date: October 2025
*/

#ifndef MACROS_H
#define MACROS_H

#define PROMPT "P1:~$ "

//* macros for general use
#define MAX_INPUT_SIZE 1024
#define SNULL -1
#define ARGS_MAX 25
#define PREDEFINED_DF 10
#define UNUSED(f)  \
    do             \
    {              \
        (void)(f); \
    } while (0) //* to avoid warnings of unused variables   
#define FLAG_LONG  (1 << 0)  
#define FLAG_ACC   (1 << 1)  
#define FLAG_LINK  (1 << 2)  
#define FLAG_HID   (1 << 3)  
#define FLAG_AVOID (1 << 4)  
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
authors [-n] \n\
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
historic [N] \n\
Repeats command number N. \n\
historic [-N] \n\
Prints only the last N commands.\n\
historic [-clear] \n\
Clears the historic.\n\
historic [-count] \n\
Prints the number of commands in the historic."
#define SHORT_HELP_OPEN "open [file] [mode]"
#define LONG_HELP_OPEN "Lists the shell open files.\n\
open [file] [mode]\n\
Opens a file and adds it the to the list of shell open files. \n\
modes:\n\
cr: O_CREAT\t ap: O_APPEND\t ex: O_EXCL\t ro: O_RDONLY\n\
rw: O_RDWR\t wo: O_WRONLY\t tr: O_TRUNC"
#define SHORT_HELP_CLOSE "close [fd]"
#define LONG_HELP_CLOSE "Closes the df file descriptor and eliminates the corresponding item from the list."
#define SHORT_HELP_DUP "dup [fd]"
#define LONG_HELP_DUP "Duplicates the df file descriptor creating the corresponding new entry on the file list."
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
#define SHORT_HELP_CREATE "create [-f] [nam]"
#define LONG_HELP_CREATE "Creates a directory of name nam.\n\
create [-f] [nam]\n\
Create a file of name nam."
#define SHORT_HELP_SETDIRPARAMS "setdirparams [long | short] [link | nolink] [hid | nohid] [reca | recb | norec]"
#define LONG_HELP_SETDIRPARAMS "Sets the parameters for listing with dir:\n\
setdirparams [long | short]\n\
long or short format.\n\
setdirparams [link | nolink]\n\
with or without symbolic links.\n\
setdirparams [hid | nohid]\n\
with or without hidden files.\n\
setdirparams [reca | recb | norec]\n\
recurse directories (after), recurse directories (before) or no recurse."
#define SHORT_HELP_GETDIRPARAMS "getdirparams"
#define LONG_HELP_GETDIRPARAMS "Shows the value of the parameters for listing with dir."
#define SHORT_HELP_DIR "dir [-d] [n1] [n2] [n3]  [...]"
#define LONG_HELP_DIR "Shows information for files/dirs n1,n2,n3,...\n\
dir [-d] [n1] [n2] [n3]  [...]\n\
list the contents of directories n1,n2,n3,..."
#define SHORT_HELP_ERASE "erase [n1] [n2] [n3] [...]"
#define LONG_HELP_ERASE "Erases files or empty directories n1,n2,n3,..."
#define SHORT_HELP_DELREC "delrec [n1] [n2] [n3] [...]"
#define LONG_HELP_DELREC "Erases files or directories n1,n2,n3,... recursively."
#define SHORT_HELP_LSEEK "lseek [df] [off] [ref]"
#define LONG_HELP_LSEEK "Positions the offset in an open file.\n\
lseek [df] [off] [ref]\n\
df: file descriptor for the open file.\n\
off: new offset.\n\
ref: reference, SEEK_SET (offset is from the beginning),\n\
SEEK_CUR (offset is from the current position),\n\
SEEK_END (offset is form the end)."
#define SHORT_HELP_WRITESTR "writestring [df] [str]"
#define LONG_HELP_WRITESTR "Writes a string str in the open file with descriptor df."
//*end of macros for help texts

#endif /* MACROS_H */