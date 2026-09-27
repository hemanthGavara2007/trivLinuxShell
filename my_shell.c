
#include "my_shell.h"
#include <stdlib.h>
#include <string.h>


int main() {
    char* input = (char*)calloc(sizeof(char),1024);
    struct dirent* entry;
    command_makeglobalenv();
    while (1) {
        printf("\n \n triv> ");
        fgets(input,1024,stdin);



        if (strcmp(input,"quit\n") == 0) {
            printf("Thnx for trying it out");
            break;
        }
        char **tokens = parse_input(input);

        if (strcmp(tokens[0],"echo") == 0 && tokens[2] == NULL) {
            command_echo(tokens[1]);
        }

        if (strcmp(tokens[0],"pwd") == 0) {
            if (strstr(command_pwd(),"trivLinuxShell") != NULL) {
                printf("%s",strstr(command_pwd(),"trivLinuxShell"));
            }
        }

        if (strcmp(tokens[0],"cd") == 0) {
            command_cd(tokens[1]);

        }
        if (strcmp(tokens[0],"ls") == 0 ) {
                command_ls(tokens[1]);

        }
        if (strcmp(tokens[0],"clear") == 0) {
            command_clear();
        }
        if (strcmp(tokens[0],"which") == 0) {
            if (command_which(tokens[1]) == NULL) {
                printf("Command not found");
            }
            else {
                printf("%s",command_which(tokens[1]));
            }
        }
        if (strstr(tokens[0],"$") && strstr(tokens[0],"=")) {
            char* ident = calloc(20,sizeof(char));
            char* value = calloc(20,sizeof(char));

            int i = 1;
            int j = 1;
            while (tokens[0][i] != '=') {
                ident[i - 1] = tokens[0][i];
                i++;
            }
            tokens[0][i] = '\0';
            j = i + 1;
            i = 0;
            while (tokens[0][j] != '\n') {
                value[i++] = tokens[0][j++];
            }
            tokens[0][j] = '\0';
            printf("%s %s",ident,value);
            command_makelocalenv(ident,value);
        }
    }
}
