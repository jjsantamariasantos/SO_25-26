
#ifndef MACROS_H
#define MACROS_H

//* macros for general use
#define MAX_INPUT_SIZE 1024
#define SNULL -1
#define ARGS_MAX 10
#define UNUSED(f) do { (void)(f); } while (0) //* to avoid warnings of unused variables

//* end of macros for general use
#define SHORT_HELP_AUTHORS "authors [-l][-n]"
#define LONG_HELP_AUTHORS "Prints the names and logins of the program authors.\n\
                            authors [-l] \n\
                            prints only the logins. \n\
                            authors -[n] \n\
                            prints only the names."
#define SHORT_HELP_GETPID "getpid [-p]"
#define LONG_HELP_GETPID "Prints the PID of the current process.\n\
                            getpid [-p] \n\
                            prints the PID of the parent process."
#define SHORT_HELP_CHDIR "chdir [dir]"
#define LONG_HELP_CHDIR "prints the current working directory.\n\
                            chdir [dir] \n\
                            changes the current working directory to 'dir'."
#define SHORT_HELP_GETCWD "getcwd"  
#define LONG_HELP_GETCWD "prints the current working directory."
#define SHORT_HELP_DATE "date [-t][-d]"
#define LONG_HELP_DATE "prints the current date and time.\n\
                            date [-t] \n\
                            prints the current time in format hh:mm:ss\n\
                            date [-d] \n\
                            prints the current date in format DD/MM/YYYY"
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
#define LONG_HELP_OPEN "Opens a file and adds it the to the list of shell open files.\n\
                            open\n\
                            lists the shell open files. \n\
                            modes:\n\
                            cr: O_CREAT\t ap: O_APPEND\t ex: O_EXCL\t ro: O_RDONLY\n\
                            rw: O_RDWR\t wo: O_WRONLY\t tr: O_TRUNC"
#define SHORT_HELP_CLOSE "close [fd]"
#define LONG_HELP_CLOSE
//*macros for help texts

//end of macros for help texts
#endif  /* MACROS_H */