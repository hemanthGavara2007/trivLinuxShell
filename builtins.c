


#include "my_shell.h"

void command_cd(char* args) {
    char* rel_path = strstr(command_pwd(),"trivLinuxShell/");
    char* abs_path = command_pwd();

    if (strcmp(args,".") == 0) { // if it is cd . , then do nothing(home directory)

    }
    else if (strcmp(args,"..") == 0) {
        if (rel_path  != NULL) { // checks for any restricted access , if not executes chdir
            chdir(rel_path);
        }
        else {
            printf("Outside access is not allowed");
        }
    }
    else if (args != NULL){
        chdir(args);
        if(strstr(command_pwd(),"trivLinuxShell") == NULL){
            chdir(abs_path);
            printf("Access not allowed");
        }
        
    }
}

char* command_pwd() {
    char* cwd = getcwd(NULL,0); // gets you the present working directory
    

    if (cwd == NULL) {
        printf("\n Error: Directory is not existing");
    }
    return cwd;
}


void command_ls(char* args) {
    struct dirent* entry; // structure to store the output by the dirent function
    if (args == NULL) {
        printf("Error: Expected argument");
    }
    DIR* dir = opendir(args); // opens the directory and returns a DIR pointer

    if (dir == NULL) {
        printf("The directory does not exist");
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s \n", entry->d_name); // loop to print all names
    }
}

void command_clear() {
#ifdef WIN_32 // if it is windows 32 , then it uses cls
    system("cls");
#else // else it uses clear
    system("clear");
#endif
}
void command_makeEnvMain() { // creation and initialization of global variables


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

    setenv(path -> ident,path-> value,1); // very important commands to set the variables
    setenv(home -> ident,home-> value,1);
    setenv(shell -> ident,shell-> value,1);
}

char* command_getEnv(char* ident) {
    return getenv(ident); //  to get the assigned shell variables
}
void command_makeEnvSub(char* ident,char* value) {

    setenv(ident,value,1);
}
void command_export(char* ident) {
   return; // not yet working , will be done on future versions
}
void command_deleteEnv(char* ident) {
    unsetenv(ident);
}
void command_deleteglobal(char* ident) {
    return; // not yet working , will be done on future versions
}

char* command_which(char* args) {

    int i = 0;
    char* loc = NULL;
    for (i = 0; commands[i] != NULL; i++) {
        if (strcmp(args,commands[i]) == 0) { // checks whether the command or symbol exists in the shell or not
            loc = calloc(sizeof(char),70);
            strcpy(loc,"/builtins.c");
            break;
        }
    }
return loc;

}

void command_echo(char* args) {
    char* s = strstr(args,"$"); //  implementation of echo
    if (s) {
        printf("%s",getenv((s+1)));
        return;
    }
    printf("%s",args);
}

void command_quit() {
    for (int i = 0; i < 70;i++) {

        if (lv[i] != NULL) {
            unsetenv(lv[i]); // unsets the variables
        }
    }

    printf("\nSaving variables !!\n");
    printf("Thnx for trying out");
    exit(0);
}
void handler(int num) {
    printf("\n The process is terminated\n");
    command_quit(); // when you press Ctrl + C
}

int cOrGFile(char* fn ,char* args,char* out) {
    FILE * fp = fopen(fn,args);
    int i = 0; // initially assumed a failure
    // used to get a file or either creates a file if not exists
    if (fp != NULL) {
        fputs(out,fp);
        fputs("\n",fp);
        i = 1;
        fclose(fp);
    }
    return i;
}
char* command_sleep(char* in) {
    int len = 0;
    while (in[len] != '\0') {

        if (!isdigit(in[len])) {
            char* msg = calloc(70,sizeof(char));
            printf("%c",in[len]);
            strcpy(msg,"\n Enter a digit");
            printf("\n Error inside sleep of is digit");
            return msg;
        }
    }

    int j = atoi(in); // conversion of characters to numbers
    // Storing start time
    clock_t start_time = clock();

    // Looping till required time is not achieved
    while ((clock() - start_time) < (j * CLOCKS_PER_SEC)) {
// a loop till we get the condition to fail
    }
    return NULL;

}

int command_mkdir(char* path,char* name){ // still in implementation
    int x = 0;
    x = mkdir(name,0777);
    return x;

}