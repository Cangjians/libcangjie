#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include <cangjie.h>



typedef enum CangjieCliMode {
    CANGJIE_CLI_MODE_CODE      = 0,
    CANGJIE_CLI_MODE_SHORTCODE = 1,
    CANGJIE_CLI_MODE_RADICAL   = 2,
} CangjieCliMode;


void usage(const char *progname) {
    printf("Usage: %s [OPTIONS]... CODE\n", basename(progname));
    printf("A CLI interface of libcangjie cangjie code query\n\n");
    printf("-f, --filter=FILTER1,FILTER2...  specify the filters used in the query\n");
    printf("                                 default: big5,hkscs\n");
    printf("                                 acceptable values:\n");
    printf("                                   big5, hkscs, punctuation, chinese,\n");
    printf("                                   zhuyin, kanji, katakana, symbols\n");
    printf("-m, --mode=MODE                  specify the mode of query\n");
    printf("                                 default: code\n");
    printf("                                 acceptable values:\n");
    printf("                                   code, shortcode, radical\n");
    printf("-C, --cj-version=VERSION         specify the version of Cangjie used\n");
    printf("                                 default: 3\n");
    printf("                                 acceptable values: 3, 5\n");
    printf("-h, --help                       print this help message and leave\n");
    printf("\nFor complete documentation, please go to our website: \n");
    printf("<http://cangjians.github.io/>\n");
}


void print_error(char *msg) {
    printf("libcangjie_cli: %s\n", msg);
    printf("Try 'libcangjie_cli --help' for more information\n");
}


int main(int argc, char **argv) {
    char *code;
    Cangjie *cj;
    int ret;
    CangjieCharList *chars;
    CangjieCharList *iter;
    CangjieChar *c;

    // variables to parse options
    int opt;
    int option_index;

    // option flags
    int opt_filter;
    CangjieCliMode opt_mode;
    int opt_cj_version;

    // helper variable(s)
    char errmsg[255];
    char *code_ptr;
    char *ptr_radical;

    // available options
    static struct option long_options[] = {
        {"filter", required_argument, 0, 'f'},
        {"mode", required_argument, 0, 'm'},
        {"cj-version", required_argument, 0, 'C'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

    // default options
    opt_filter = CANGJIE_FILTER_BIG5 | CANGJIE_FILTER_HKSCS;
    opt_mode = CANGJIE_CLI_MODE_CODE;
    opt_cj_version = CANGJIE_VERSION_3;

    // read options
    while (1) {
        option_index = 0;
        opt = getopt_long(argc, argv, "f:m:C:h", long_options, &option_index);

        if (opt == -1) {
            break; 
        }

        switch (opt) {
            case 'f':
                opt_filter = 0;
                if (strstr(optarg, "big5") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_BIG5;
                }
                if (strstr(optarg, "hkscs") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_HKSCS;
                }
                if (strstr(optarg, "puntuation") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_PUNCTUATION;
                }
                if (strstr(optarg, "chinese") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_CHINESE;
                }
                if (strstr(optarg, "zhuyin") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_BIG5;
                }
                if (strstr(optarg, "kanji") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_KANJI;
                }
                if (strstr(optarg, "katakana") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_KATAKANA;
                }
                if (strstr(optarg, "hiragana") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_HIRAGANA;
                }
                if (strstr(optarg, "symbols") != NULL) {
                    opt_filter = opt_filter | CANGJIE_FILTER_SYMBOLS;
                }
                if (opt_filter == 0) {
                    sprintf(errmsg, "Invalid filter option '%s'", optarg);
                    print_error(errmsg);
                    return -1;
                }
                break;
            case 'm':
                if (strcmp(optarg, "code") == 0) {
                    opt_mode = CANGJIE_CLI_MODE_CODE;
                } else if (strcmp(optarg, "shortcode") == 0) {
                    opt_mode = CANGJIE_CLI_MODE_SHORTCODE;
                } else if (strcmp(optarg, "radical") == 0) {
                    opt_mode = CANGJIE_CLI_MODE_RADICAL;
                } else {
                    sprintf(errmsg, "Invalid query mode '%s'", optarg);
                    print_error(errmsg);
                    return -1;
                }
                break;
            case 'u':
                if (*optarg == '3') {
                    opt_cj_version = CANGJIE_VERSION_3;
                } else if (*optarg == '5') {
                    opt_cj_version = CANGJIE_VERSION_5;
                } else {
                    sprintf(errmsg, "Invalid Cangjie version '%s'", optarg);
                    print_error(errmsg);
                    return -1;
                }
                break;
            case '?':
                printf("Try 'libcangjie_cli --help' for more information\n");
                return -1;
                break;
            case 'h':
            default:
                usage(argv[0]);
                return (opt == 'h') ? 0 : -1;
        }
    }

    // check if query provided
    if (optind == argc) {
        print_error("missing query code");
        return -1;
    }

    code = argv[optind];

    ret = cangjie_new(&cj, opt_cj_version, opt_filter);

    if (ret == CANGJIE_DBOPEN) {
        printf("Could not open the Cangjie database\n");
        return ret;
    } else if (ret != CANGJIE_OK) {
        printf("Unhandled error while creating the Cangjie object: %d\n", ret);
        return ret;
    }


    if (opt_mode == CANGJIE_CLI_MODE_RADICAL) {
        code_ptr = code;
        for (; *code_ptr != '\0'; code_ptr++) {
            ret = cangjie_get_radical(cj, *code_ptr, &ptr_radical);
            if (ret == CANGJIE_OK) {
                printf("code: '%c', radical: '%s'\n", *code_ptr, ptr_radical);
            } else {
                printf("Query error (%d)\n", ret);
                return ret;
            }
        }
        return ret;
    } else {
        if (opt_mode == CANGJIE_CLI_MODE_CODE) {
            ret = cangjie_get_characters(cj, code, &chars);
        } else if (opt_mode == CANGJIE_CLI_MODE_SHORTCODE) {
            ret = cangjie_get_characters_by_shortcode(cj, code, &chars);
        }

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
    }

    cangjie_free(cj);

    return CANGJIE_OK;
}
