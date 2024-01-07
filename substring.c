#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFLEN 256

static char main_buf[BUFLEN];

int find_substring(int fd, const char *pattern)
{
    int res = 0;
    int read_len;
    int i, j = 0;
    while ((read_len = read(fd, main_buf, BUFLEN)) > 0) {
        i = 0;
        while (i < read_len) {
            if (main_buf[i] != pattern[j]) {
                i++;
                continue;
            }
            while (i < read_len && pattern[j] &&
                   main_buf[i] == pattern[j]) {
                j++;
                i++;
            }
            if (!pattern[j]) {
                res++;
                j = 0;
            }
        }
    }
    if (fd < 0) {
        fprintf(stderr, "error while reading file\n");
        perror("read");
    }
    return res;
}
