
#include "my_shell.h"

void command_cd(char* args) {
    if (args == NULL) {
        printf("cd: Expected argument \n");
        return;
    }
    if (strcmp(args,".") == 0) {
        char* cwd = getcwd(NULL,0);
        printf("The current directory : %s",cwd);
    }
    else if (strcmp(args,"..") == 0) {
        chdir("..");
    }
}

void command_pwd() {
    char* cwd = getcwd(NULL,0);

    if (cwd != NULL) {
        printf("The current directory : %s",cwd);
        return;
    }
    printf("Error: Directory is not existing");
}

void command_ls(char* args) {
    struct dirent* entry;
    if (args == NULL) {
        printf("Error: Expected argument");
    }
    DIR* dir = opendir(args);

    if (dir == NULL) {
        printf("The directory does not exist");
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s \n", entry->d_name);
    }
}

void command_clear() {
#ifdef WIN_32
    system("cls");
#else
    system("clear");
#endif
}

void command_getbasicenv() {



}

char* command_which(char* args) {

    int i = 0;
    char* loc = NULL;
    for (i = 0; commands[i] != NULL; i++) {
        if (strcmp(args,commands[i]) == 0) {
            loc = calloc(sizeof(char),70);
            strcpy(loc,"/builtins.c");
            break;
        }
    }
return loc;

}