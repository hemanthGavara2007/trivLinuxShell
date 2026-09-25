
#include <sys/_types/_size_t.h>
#include "my_shell.h"

char** parse_input(const char* input) {

    int i = 0;
    int j = 0;
    int k = 0;
    char** tokens = calloc(sizeof(char*),70);
    char* token = calloc(sizeof(char),70);
    size_t tokcou = 0;

    while (input[i] != '\n' && input[i] != '\0') {
        token = calloc(70,sizeof(char));

        while (input[i+j] != ' ' && input[i+j] != '\"') {

            if (input[i+j] == '\n') {
                break;
            }
            token[j] = input[i+j];
            j++;

        }
        k = 1;
        if (input[i+j] == '\"') {
            j++;
            while (input[i+j] != '\"') {
                token[j - 1] = input[i+j];
                j++;
            }
            k = 2;
            j--;
        }
        token = realloc(token,(j+1) * sizeof(char));
        token[j] = '\0';
        i = i + j + k;
        tokens[tokcou++] = token;

        j = 0;
    }
    tokens = realloc(tokens,(tokcou + 1) * sizeof(char*));
    tokens[tokcou] = NULL;
    return tokens;
}
