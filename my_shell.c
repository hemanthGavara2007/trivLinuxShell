#include "my_shell.h"
#include <stdlib.h>
#include <string.h>


int main() {
    char *input = (char *) calloc(sizeof(char), 1024);
    char *out = calloc(sizeof(char), 1024); //output for pipes
    strcpy(out, "<<<"); // my version of NULL

    int suc = 1; // Stores if the command is succesful or has failure , assuming initial success
    struct dirent *entry; // for ls command functioning
    command_makeEnvMain(); // declares pwd , and other shell variables
    while (1) {
        printf(" \n triv> ");
        fgets(input, 1024,stdin);// safe way to get output
        signal(SIGINT, handler);// handles Ctrl + C

        char **tokens = parse_input(input); // see the parse_input.c file for more info 
        int n = 0;
        
        while (tokens[n] != NULL) {
            if (strcmp(input, "quit\n") == 0) {
                raise(SIGINT);
                command_clear();
                command_quit();
            }


            if (strcmp(tokens[n], "echo") == 0) {
                if (tokens[n + 2] == NULL) {
                    command_echo(tokens[n + 1]);
                    n = n + 2;
                    continue;
                }

                if (strcmp(out, "<<<") != 0 && n - 1 >= 0) {
                    if (strcmp(tokens[n - 1], "|") == 0) { // pipes execution for the echo function
                        command_echo(out);
                        n++;
                        continue;
                    }
                }
                strcpy(out, tokens[n+1]);
                n = n + 2;
                continue;
            }

            if (strcmp(tokens[n], "pwd") == 0) {
                if (strstr(command_pwd(), "trivLinuxShell") != NULL) { // used for sandboxing
                    if (tokens[n + 1] == NULL) {
                        printf("%s", strstr(command_pwd(), "trivLinuxShell"));
                    }else {
                        printf("Nope You cannot access files from outside");
                    }
                    if(tokens[n+1] != NULL){
                        if (strcmp(tokens[n + 1], "|") == 0) {
                            strcpy(out, strstr(command_pwd(),"trivLinuxShell")); //pipes for pwd
                            n = n + 2;
                            continue;
                        }
                }
                }
                n++;
                continue;
            }

            if (strcmp(tokens[n], "cd") == 0) {
                if (tokens[n + 1] == NULL) { // checks whether there is something before cd or not
                    printf("cd: Expected argument \n");
                    suc = 0;
                    continue;
                }
                if (tokens[n + 2] == NULL) {
                    command_cd(tokens[n + 1]);
                    n = n + 2;
                    continue;
                }
                if (n - 1 > 0) {
                    if (strcmp(tokens[n - 1], "|") == 0) { //pipes for cd
                        command_cd(tokens[n + 1]);
                        n = n + 2;
                        continue;
                    }
                }
            }
            if (strcmp(tokens[n], "ls") == 0) { // trying to execute pipes for ls
                command_ls(tokens[n + 1]);
                n = n + 2;
                continue;
            }
            if (strcmp(tokens[n], "clear") == 0) { // you know what it means
                if (tokens[n + 1] != NULL) {
                    printf("That isnt the correct way of using clear, use it seperately");
                    break;
                }
                command_clear();
                n++;
                continue;
            }
            if (strcmp(tokens[n], "which") == 0) { // used to know if a command exists or not
                if (command_which(tokens[n + 1]) == NULL) {
                    printf("Command not found");
                } else {
                    printf("%s", command_which(tokens[n + 1]));
                    suc = 0;
                }
            }
            if (strstr(tokens[n], "$") && strstr(tokens[n], "=")) { //shell variables stuff
                char *ident = calloc(20, sizeof(char));
                char *value = calloc(20, sizeof(char));

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
                command_makeEnvSub(ident, value);
                continue;
            }

            if (strcmp(tokens[n], "unset") == 0) {
                command_deleteEnv(tokens[n + 1]);
            }
            if (strcmp(tokens[n], "&&") == 0) { //here comes the conditionals of &&
                if (suc != 1) {
                    break;
                }
                n++;
                continue;
            }
            if (strcmp(tokens[n], "||") == 0) { // here comes the conditionals of ||
                if (suc == 1) {
                    break;
                }
                n++;
                continue;
            }

            if (strcmp(tokens[n], ">") == 0) { // redirections of overwrite here , be careful with this
                if (strcmp(out, "<<<") == 0 || (tokens[n + 1] == NULL)) {
                    printf("Looks like a error , once check the code");
                    suc = 0;
                    continue;
                }
                if (tokens[n + 1] != NULL) {
                    suc = cOrGFile(tokens[n + 1], "w", out);
                    n = n + 2;
                    if (suc == 0) {
                        printf("File has not been created");
                    }
                    continue;
                }
            }
            if (strcmp(tokens[n], ">>") == 0) { // redirections of append here
                if (strcmp(out, "<<<") == 0 || tokens[n + 1] == NULL) {
                    printf("Looks like a error , once check the code");
                    suc = 0;
                    continue;
                }
                if (tokens[n + 1] != NULL) {
                    suc = cOrGFile(tokens[n + 1], "a", out);
                    n = n + 2;
                    if (suc == 0) {
                        printf("File has not been created");
                        continue;
                    }
                }
            }
            if (strcmp(tokens[n],"sleep") == 0) { // want your shell to take rest , use this ,just kidding
                if (tokens[n+1] == NULL) {
                    printf("You should enter a number");
                    continue;
                    suc = 0;
                }
                    printf("%s",tokens[n+1]);
                    command_sleep(tokens[n+1]);
                    n = n + 2;
                    continue;
                
            }
            if(strcmp(tokens[n],"mkdir") == 0)
            {   int x;
                if (tokens[n+1] != NULL){
                    x = command_mkdir(NULL,tokens[n+1]);
                }
                if (!x){
                    suc = 0;
                }
                n = n + 2;
            }
            if (suc == 0 && tokens[n+1] == NULL) { printf("Looks like a error \n"); n = n + 2;break;}// I guess i dont need to explain this
        }
    }
}
