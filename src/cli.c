#include <stdio.h>

#include <cangjie.h>


int main(int argc, char **argv) {
    char *code;
    Cangjie *cj;
    int ret;
    CangjieCharList *chars;
    CangjieCharList *iter;
    CangjieChar *c;

    if (argc != 2) {
        printf("Usage: %s CODE\n", argv[0]);
        return -1;
    }

    code = argv[1];

    ret = cangjie_new(&cj, CANGJIE_VERSION_3,
                      CANGJIE_FILTER_BIG5 | CANGJIE_FILTER_HKSCS);
    if (ret == CANGJIE_DBOPEN) {
        printf("Could not open the Cangjie database\n");
        return ret;
    } else if (ret != CANGJIE_OK) {
        printf("Unhandled error while creating the Cangjie object: %d\n", ret);
        return ret;
    }

    ret = cangjie_get_characters(cj, code, &chars);

    if (ret == CANGJIE_NOCHARS) {
        printf("No chars with code '%s'\n", code);

        cangjie_free(cj);
        return CANGJIE_NOCHARS;
    }

    iter = chars;

    while (1) {
        if (iter == NULL) {
            break;
        }

        c = iter->c;
        printf("Char: %s, code: '%s', classic frequency: %d\n",
               c->chchar, c->code, c->frequency);

        iter = iter->next;
    }

    cangjie_char_list_free(chars);
    cangjie_free(cj);

    return CANGJIE_OK;
}
