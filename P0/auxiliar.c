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
    {NULL, NULL, NULL, NULL} //* end marker
};