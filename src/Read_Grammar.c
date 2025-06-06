#include "Read_Grammar.h"

#define MAX_LINE 512
#define MAX_SYMBOLS 64

void strip_newline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

char* trim_whitespace(char* str) {
    while (*str == ' ' || *str == '\t') str++;
    if (*str == '\0') return str;

    char* end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t')) end--;

    *(end + 1) = '\0';
    return str;
}

void Load_Grammar_From_File(const char* filename, ProductionSalver* salver) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening grammar file");
        exit(1);
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        strip_newline(line);
        if (strlen(line) == 0 || line[0] == '#') continue;

        char* arrow = strstr(line, "->");
        if (!arrow) {
            fprintf(stderr, "Invalid production format: %s\n", line);
            continue;
        }

        *arrow = '\0';
        char* lhs_raw = trim_whitespace(line);
        char* rhs_raw = trim_whitespace(arrow + 2);

        // Copia segura de lhs
        char lhs_copy[128];
        strncpy(lhs_copy, lhs_raw, sizeof(lhs_copy));
        lhs_copy[sizeof(lhs_copy)-1] = '\0';

        // Tokenizar RHS
        char* token = strtok(rhs_raw, " \t\n");
        int count = 0;
        char* rhs[MAX_SYMBOLS];
        while (token != NULL && count < MAX_SYMBOLS) {
            rhs[count++] = token;
            token = strtok(NULL, " \t\n");
        }

        Production prod = Create_Production(lhs_copy, rhs, count);
        Save_Production(salver, prod);
    }

    fclose(file);
}
