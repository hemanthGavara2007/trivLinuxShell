#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

char** parse_input(const char* input);
void command_cd(char* args);
char* command_pwd();
void command_ls(char* args);
void command_clear();
char* command_which(char* args);
void command_makeglobalenv();
char* command_getenv(char* ident);
void command_makelocalenv(char* ident, char* value);
void command_echo(char* args);
void command_quit();
void command_deletelocal(char* ident);
void command_deleteglobal(char* ident);
void command_export(char* ident);

typedef struct env {
    char* ident;
    char* value;
}env;

static char* commands[] = {"cd","env","pwd","ls","clear","echo","which",NULL};
char **lv;