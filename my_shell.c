
#include "my_shell.h"
#include <stdlib.h>
#include <string.h>


int main() {
    char* input = (char*)calloc(sizeof(char),1024);
    char* out = calloc(sizeof(char),1024);
    strcpy(out,"<<<");

    int suc = 1;
    struct dirent* entry;
    command_makeEnvMain();
    while (1) {
        printf(" \n triv> ");
        fgets(input,1024,stdin);
        signal(SIGINT,handler);
        char **tokens = parse_input(input);
        int n = 0;

        while (tokens[n] != NULL){
        if (strcmp(input,"quit\n") == 0) {
            raise(SIGINT);
            command_clear();
            command_quit();
        }


        if (strcmp(tokens[n],"echo") == 0) {
            if (tokens[n+2] == NULL){
                command_echo(tokens[n+1]);
                n++;
                continue;
            }

            if (strcmp(out,"<<<") != 0 && (strcmp(tokens[n-1],"|") == 0)) {
                command_echo(out);
                n++;
                continue;
            }
            strcpy(out,tokens[n+1]);
            n = n + 2;

        }

        if (strcmp(tokens[n],"pwd") == 0) {

            if (strstr(command_pwd(),"trivLinuxShell") != NULL) {
                if (tokens[n+1] == NULL){
                printf("%s",strstr(command_pwd(),"trivLinuxShell"));
            }
                if (strcmp(tokens[n+1],"|") == 0) {
                    strcpy(out,strstr(command_pwd(),"trivLinuxShell"));
                    n =  n + 2;
                    continue;
                }
            }
            n++;
            continue;
        }

        if (strcmp(tokens[n],"cd") == 0) {
            if (tokens[n+1] == NULL) {
                printf("cd: Expected argument \n");
                suc = 0;
                continue;
            }
           if (tokens[n+2] == NULL) {
               command_cd(tokens[n+1]);
               n = n + 2;
               continue;
           }
            if (n - 1 > 0) {
                if (strcmp(tokens[n-1],"|") == 0) {
                    command_cd(tokens[n+1]);
                    n = n + 2;
                    continue;
                }
            }
        }
        if (strcmp(tokens[n],"ls") == 0 ) {
            command_ls(tokens[n+1]);
            n = n + 2;
            continue;

        }
        if (strcmp(tokens[n],"clear") == 0) {

            if (tokens[n+1] != NULL) {
                printf("That isnt the correct way of using clear, use it seperately");
                break;
            }
            command_clear();
            n++;
            continue;

        }
        if (strcmp(tokens[n],"which") == 0) {
            if (command_which(tokens[n+1]) == NULL) {
                printf("Command not found");
            }
            else {
                printf("%s",command_which(tokens[n + 1]));
                suc = 0;
            }
        }
        if (strstr(tokens[n],"$") && strstr(tokens[n],"=")) {
            char* ident = calloc(20,sizeof(char)); // There is a error here , solve it
            char* value = calloc(20,sizeof(char));

            int i = 1;
            int j = 1;
            while (tokens[n][i] != '=') {
                ident[i - 1] = tokens[0][i];

                i++;
            }
            ident[i - 1] = '\0';
            j = j + i;
            i = 0;
            printf("\n");
            while (tokens[n][j] != '\0') {
                value[i] = tokens[n][j];
                j++;
                i++;
            }
            value[i] = '\0';
            command_makeEnvSub(ident,value);
            continue;

        }

        if (strcmp(tokens[n],"unset") == 0) {
            command_deleteEnv(tokens[n+1]);
        }
        if (strcmp(tokens[n],"&&") == 0) {
            if (suc != 1) {
                break;
            }
            n++;
            continue;
        }
        if (strcmp(tokens[n],"||") == 0) {
            if (suc == 1) {
                break;
            }
            n++;
            continue;
        }

        if (strcmp(tokens[n],">") == 0) {
            if (strcmp(out,"<<<") == 0 || tokens[n+1] == NULL) {
                printf("Looks like a error , once check the code");
                suc = 0;
                continue;
            }
            if (tokens[n+1] != NULL) {
                suc = cOrGFile(tokens[n+1],"w",out);
                n = n + 2;
                if (suc == 0) {
                    printf("File has not been created");
                }
            }

        }
            if (strcmp(tokens[n],">>") == 0) {
                if (strcmp(out,"<<<") == 0 || tokens[n+1] == NULL) {
                    printf("Looks like a error , once check the code");
                    suc = 0;
                    continue;
                }
                if (tokens[n+1] != NULL) {
                    suc = cOrGFile(tokens[n+1],"a",out);
                    n = n + 2;
                    if (suc == 0) {
                        printf("File has not been created");
                        continue;
                    }
                }

            }

            if (suc == 0){printf("Looks like a error \n");n++;}

    }

    }
}
