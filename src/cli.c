#include <stdio.h>

#include <cangjie.h>


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s CODE\n", argv[0]);
        return 1;
    }

    char *code = argv[1];

    Cangjie *cj = cangjie_new(CANGJIE_VERSION_3,
                              CANGJIE_FILTER_BIG5 | CANGJIE_FILTER_HKSCS);
    CangjieCharList *chars = cangjie_get_characters(cj, code);
    
    if (chars == NULL) {
        printf("No chars with code '%s'\n", code);

        cangjie_free(cj);
        return 1;
    }
    
    CangjieCharList *iter = chars;
    CangjieChar *c;

    while (1) {
        if (iter == NULL) {
            break;
        }

        c = iter->c;
        printf("Char: %s, code: '%s', classic frequency: %d\n",
               c->chchar, c->code, c->classic_freq);

        iter = iter->next;
    }

    cangjie_char_list_free(chars);
    cangjie_free(cj);

    return 0;
}
