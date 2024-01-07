#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "substring.h"

int main(int argc, const char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: <substring> <file>\n");
        return 1;
    }

    int fd;
    fd = open(argv[2], O_RDONLY, 0777);
    if (fd == -1) {
        fprintf(stderr, "unable to open a file\n");
        perror("open");
        return 2;
    }
    int res = find_substring(fd, argv[1]);
    close(fd);
    /*
        process arguments
        usage: [args] <pattern> [file]
        or
        usage: <pattern> [file] [args]

        open a main program with arguments and processing a pattern
        print string with pattern
    */
    printf("%d\n", res);
    return 0;
}
