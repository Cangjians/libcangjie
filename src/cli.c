#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <cangjie.h>


int main(int argc, char **argv) {
    char *code;
    Cangjie *cj;
    int ret;
    CangjieCharList *chars;
    CangjieCharList *iter;
    CangjieChar *c;
    int opt;
    int option_index;

    // available options
    static struct option long_options[] = {
        {"with-filter", required_argument, 0, 'f'},
        {"mode", required_argument, 0, 'm'},
        {"use-cj-version", required_argument, 0, 'u'},
        {"help", no_argument, 0, 'h'},
    };

    // read options
    while (1) {

        option_index = 0;
        opt = getopt_long(argc, argv, "u:m:f:h", long_options, &option_index);

        if (opt == -1) break;

        switch (opt) {
          case 'f':
            // TODO: option --with-filter with optarg
            break;
          case 'm':
            // TODO: option --mode with optarg
            break;
          case 'u':
            // TODO: option --use-cj-version with optarg
            break;
          case 'h':
          default:
            print_help();
            return (opt == 'h') ? EXIT_SUCCESS : EXIT_FAILURE;
        }
    }

    // check if query provided
    if (optind == argc) {
        printf("libcangjie2_cli: missing query code\n");
        printf("Try 'libcangjie2_cli --help' for more information\n");
        return EXIT_FAILURE;
    }


    code = argv[optind];

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


int print_help() {
    printf("Usage: libcangjie2_cli [OPTIONS]... CODE\n");
    printf("A CLI interface of libcangjie2 cangjie code query\n\n");
    printf("-f, --with-filter=FILTER1,FILTER2...  specify the filters used in the query\n");
    printf("                                      acceptable values:\n");
    printf("                                        big5, hkscs, punctuation, chinese,\n");
    printf("                                        zhuyin, kanji, katakana, symbols\n");
    printf("-m, --mode=MODE                       specify the mode of query\n");
    printf("                                      acceptable values: \n");
    printf("                                        code, shortcode\n");
    printf("-u, --use-cj-version=VERSION          specify the version of Cangjie used\n");
    printf("                                      acceptable values: 3, 5\n");
    printf("-h, --help                            print this help message and leave\n");
    printf("\nFor complete documentation, please go to our website: \n");
    printf("<http://cangjians.github.io/>\n");
}
