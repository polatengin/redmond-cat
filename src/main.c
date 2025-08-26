#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define REDMOND_CAT_VERSION "1.0"

int main(int argc, char *argv[]) {
    int opt;
    int number_all = 0;
    int squeeze_blank = 0;

    // Parse options (-n, -s, plus long opts --help, --version)
    while ((opt = getopt(argc, argv, "ns-:")) != -1) {
        switch (opt) {
            case 'n': number_all = 1; break;
            case 's': squeeze_blank = 1; break;
            case '-':
                if (strcmp(optarg, "help") == 0) {
                    printf("Usage: %s [OPTIONS] [FILE...]\n", argv[0]);
                    printf("Concatenate files to standard output.\n\n");
                    printf("Options:\n");
                    printf("  -n           Number all output lines\n");
                    printf("  -s           Squeeze multiple blank lines into one\n");
                    printf("  --help       Show this help and exit\n");
                    printf("  --version    Show version information\n");
                    return 0;
                } else if (strcmp(optarg, "version") == 0) {
                    printf("redmond-cat %s\n", REDMOND_CAT_VERSION);
                    return 0;
                } else {
                    dprintf(STDERR_FILENO, "%s: unrecognized option '--%s'\n", argv[0], optarg);
                    return 1;
                }
                break;
            default:
                dprintf(STDERR_FILENO, "Usage: %s [-n] [-s] [FILE...]\n", argv[0]);
                return 1;
        }
    }

    int file_index = optind;
    int line_number = 1;
    int prev_blank = 0;

    if (file_index == argc) {
        argv[argc++] = "-"; // no files given → read stdin
    }

    for (; file_index < argc; file_index++) {
        FILE *fp;
        if (strcmp(argv[file_index], "-") == 0) {
            fp = stdin;
        } else {
            fp = fopen(argv[file_index], "r");
            if (!fp) {
                dprintf(STDERR_FILENO, "%s: %s: %s\n",
                        argv[0], argv[file_index], strerror(errno));
                continue;
            }
        }

        char *line = NULL;
        size_t len = 0;
        ssize_t nread;
        while ((nread = getline(&line, &len, fp)) != -1) {
            if (squeeze_blank && line[0] == '\n') {
                if (prev_blank) continue;
                prev_blank = 1;
            } else {
                prev_blank = 0;
            }

            if (number_all) {
                printf("%6d\t%s", line_number++, line);
            } else {
                fputs(line, stdout);
            }
        }

        free(line);
        if (fp != stdin) fclose(fp);
    }

    return 0;
}
