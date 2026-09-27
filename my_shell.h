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
char* command_getglobalenv(char* ident);
void command_makelocalenv(char* ident, char* value);
void command_echo(char* args);

typedef struct env {
    char* ident;
    char* value;
}env;

static char* commands[] = {"cd","env","pwd","ls","clear","echo","which",NULL};
env **lv;
static int lvc = 3;