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
#define SHORT_HELP_CLOSE "close [df]"
#define LONG_HELP_CLOSE "Closes the df file descriptor and eliminates the corresponding item from the list."
#define SHORT_HELP_DUP "dup [df]"
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
#define SHORT_HELP_MALLOC "malloc [-free] [n]"
#define LONG_HELP_MALLOC "Lists the blocks allocated with the malloc command. \n\
malloc [n]\n\
Allocates a block of malloc memory of size n bytes. Updates the list of memory blocks. \n\
malloc [-free] [n]\n\
Deallocates a block of malloc memory of size n (provided it has been previously allocated with allocate). \
Updates the list of memory blocks. If there is more than one block of size n allocated, deallocates ONE of them"
#define SHORT_HELP_MMAP "mmap [-free] [fich] [perm]"
#define LONG_HELP_MMAP "Lists the blocks allocated with the mmap command. \n\
mmap [fich] [perm]\n\
Maps the file fich to memory with permissions perm. (perm is in the format rwx, ---). Updates the list of memory blocks\n\
mmap [-free] [fich]\n\
Unmaps file fich from memory (provided it has been previously mapped).Updates the list of memory blocks. \
If fich has been mapped several times, it unmaps ONE of them."
#define SHORT_HELP_SHARED "shared [-create | free | delkey] [cl] [n]"
#define LONG_HELP_SHARED "Lists the blocks allocated with the shared command. \n\
shared [-create] [cl] [n]\n\
Creates a block of shared memory with key cl and size n and attaches it to the process address space. \
Updates the list of memory blocks.\n\
shared[cl]\n\
Attaches a block of shared memory with key cl to the process address space (the block must be already created but \
not necessarily attached to the process space). Updates the list of memory blocks.\n\
shared [-free] [cl]\n\
Detaches a block of shared memory of key cl (provided it has been previously allocated). \
Updates the list of memory blocks.\n\
shared [-delkey] [cl]\n\
Removes de memory block of key cl from the system. IT DOES NOT DETACH THE SHARED MEMORY WITH THAT KEY SHOULD IT BE ATTACHED."
#define SHORT_HELP_FREE "free [addr]"
#define LONG_HELP_FREE "Deallocates the block with address addr. (if it is a malloc block, it frees it; if it is a shared memory block, it detaches it….). \
Updates the list of memory blocks."
#define SHORT_HELP_MEMFILL "memfill [addr] [cont] [ch]"
#define LONG_HELP_MEMFILL "Fills the memory with character ch, starting at address addr, for cont bytes."
#define SHORT_HELP_MEMDUMP "memdump [addr] [cont]"
#define LONG_HELP_MEMDUMP "Dumps the contents of cont bytes of memory at address addr to the screen. \
Dumps hex codes, and for printable characters the associated character. \
Newline, tabs, carriage returns, should be printed as in C:'\n', '\t' and '\r'."
#define SHORT_HELP_MEM "mem [-funcs] [-vars] [-blocks] [-all] [-pmap]"
#define LONG_HELP_MEM "mem [-funcs] \n\
Prints the addresses of 3 program functions and 3 library functions.\n\
mem [-vars] \n\
Prints the addresses of 3 external, 3 external initialized, 3 static, 3 static initialized and 3 automatic variables.\n\
mem [-blocks] \n\
Prints the list of allocated blocks (with malloc, shared and pmap).\n\
mem [-all] \n\
Prints all of the above (-funcs, -vars and -blocks).\n\
mem [-pmap] \n\
Shows the output of the command pmap for the shell process (vmmap en macos)."
#define SHORT_HELP_READFILE "readfile [file] [addr] [cont]"
#define LONG_HELP_READFILE "Reads cont bytes of a file into memory address addr."
#define SHORT_HELP_WRITEFILE "writefile [file] [addr] [cont]"
#define LONG_HELP_WRITEFILE "Writes to a file cont bytes starting at memory address addr."
#define SHORT_HELP_READ "read [df] [addr] [cont]"
#define LONG_HELP_READ "Reads cont bytes of a file with an already opened df into memory address addr."
#define SHORT_HELP_WRITE "write [df] [addr] [cont]"
#define LONG_HELP_WRITE "Writes to a file with an already opened df cont bytes starting at memory address addr."
#define SHORT_HELP_RECURSE "recurse [n]"
#define LONG_HELP_RECURSE  "Executes the recursive function n times. This funcion has an automatic array of size 1024, \
a static array of size 1024 and prints the addresses of both arrays and its parameter (as well as the number of recursion) before calling itself."
//*end of macros for help texts

#endif /* MACROS_H */