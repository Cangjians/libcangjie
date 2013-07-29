#include <stdlib.h>
#include <string.h>


void append_string(char **str, const char *to_append) {
    int len = strlen(to_append);
    int total_len = len;
    char *p;

    if (*str == NULL) {
        p = calloc(total_len + 1, sizeof(char));
    } else {
        total_len = strlen(*str) + len;
        p = realloc(*str, (total_len + 1) * sizeof(char));
    }

    strncat(p, to_append, len);
    p[total_len] = '\0';
    *str = p;
}
