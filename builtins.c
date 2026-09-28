
#include "my_shell.h"

void command_cd(char* args) {
    if (args == NULL) {
        printf("cd: Expected argument \n");
        return;
    }
    if (strcmp(args,".") == 0) {

    }
    else if (strcmp(args,"..") == 0) {
        if (strstr(command_pwd(),"trivLinuxShell/") != NULL) {
            chdir("..");
        }
        else {
            printf("Outside access is not allowed");
        }
    }
}

char* command_pwd() {
    char* cwd = getcwd(NULL,0);

    if (cwd == NULL) {
        printf("\n Error: Directory is not existing");
    }
    return cwd;
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
void command_makeglobalenv() {


    char* a = calloc(sizeof(char),70);
    char* b = calloc(sizeof(char),70);
    strcpy(a,"PATH");
    strcpy(b,"trivLinuxShell/builtins.c");
    env path1 = {a,b};
    env *path = &path1;
    char* c = calloc(sizeof(char),70);
    char* d = calloc(sizeof(char),70);
    strcpy(c,"SHELL");
    strcpy(d,"trivLinuxShell/my_shell.c");
    env shell1 = {c,d};
    env *shell = &shell1;
    char* e = calloc(sizeof(char),70);
    char* f = calloc(sizeof(char),70);
    strcpy(e,"HOME");
    strcpy(f,"trivLinuxShell");
    env home1 = {e,f};
    env *home= &home1;
    lv = calloc(70,sizeof(char*));

    setenv(path -> ident,path-> value,1);
    setenv(home -> ident,home-> value,1);
    setenv(shell -> ident,shell-> value,1);
}

char* command_getenv(char* ident) {
    return getenv(ident);
}
void command_makelocalenv(char* ident,char* value) {

    for (int i = 0; i < 70; i++) {
        if (lv[i] == NULL) {
            lv[i] = ident;
            break;
        }
    }
    setenv(ident,value,1);
}
void command_export(char* ident) {
    int notfound = 1;
    ident = ident + 1;

    for (int i = 0; i < 70;i++) {

        if (strcmp(ident,lv[i]) == 0) {
            lv[i] = NULL;
            notfound = 0;
        }

    }

    if (notfound) {
        printf("Local Valriable not found");
    }
}
void command_deletelocal(char* ident) {
    unsetenv(ident);
}
void command_deleteglobal(char* ident) {
    for (int i = 0; i < 70;i++) {

        if (strcmp(ident,lv[i]) == 0) {
            lv[i] = ident;
        }

    }
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

void command_echo(char* args) {
    char* s = strstr(args,"$");
    if (s) {
        printf("%s",getenv((s+1)));
    }
}

void command_quit() {
    for (int i = 0; i < 70;i++) {

        if (lv[i] != NULL) {
            unsetenv(lv[i]);
        }
    }

    printf("Saving variables !!");
    printf("Thnx for trying out");
    exit(0);
}