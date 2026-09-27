#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

char** parse_input(const char* input);
void command_cd(char* args);
void command_pwd();
void command_ls(char* args);
void command_clear();
char* command_which(char* args);
static char* commands[] = {"cd","env","pwd","ls","clear","echo","which",NULL};