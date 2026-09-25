
#include "my_shell.h"
#include <stdlib.h>
#include <string.h>


int main() {
    char* input = (char*)calloc(sizeof(char),1024);
    struct dirent* entry;
    while (1) {

        printf("\n triv> ");
        fgets(input,1024,stdin);
        printf("Input given : %s",input);

        if (strcmp(input,"quit\n") == 0) {
            printf("Thnx for trying it out");
            break;
        }
        char **tokens = parse_input(input);

        if (strcmp(tokens[0],"echo") == 0 && tokens[2] == NULL) {
            printf("%s",tokens[1]);
        }

        if (strcmp(tokens[0],"pwd") == 0) {

            command_pwd();
        }
        if (strcmp(tokens[0],"cd") == 0) {
            command_cd(tokens[1]);

        }
        if (strcmp(tokens[0],"ls") == 0 ) {
            DIR* dir = opendir(".");
           if (tokens[2] ==  NULL) {
               dir = opendir(tokens[2]);
           }


            if (dir == NULL) {
                printf("The directory does not exist");
            }

            while ((entry = readdir(dir)) != NULL) {
                printf("%s \n", entry->d_name);
            }
        }
    }
}
