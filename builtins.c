
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
    printf("Error: Directory is not ")
}