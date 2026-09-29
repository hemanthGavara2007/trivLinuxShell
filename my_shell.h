#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>

char** parse_input(const char* input);
void command_cd(char* args);
char* command_pwd();
void command_ls(char* args);
void command_clear();
char* command_which(char* args);
void command_makeEnvMain();
char* command_getEnv(char* ident);
void command_makeEnvSub(char* ident, char* value);
void command_echo(char* args);
void command_quit();
void command_deleteEnv(char* ident);
void command_deleteglobal(char* ident);
void command_export(char* ident);
void handler(int num);
typedef struct env {
    char* ident;
    char* value;
}env;

static char* commands[] = {"cd","env","pwd","ls","clear","echo","which",NULL};
char **lv;