#include <stdio.h>
#include <stdlib.h>

#define BUFLEN 12 

const char* str_str(const char* pattern, const char* str, int len)
{
    int i;
    for (i = 0; i < len && str[i]; i++) {
        if (str[i] != *pattern)
            continue;
        int j;
        for (j = 1; j < len && str[i + j] && str[i + j] == pattern[j]; j++)
            {}
        if (!pattern[j])
            return str + i;
    }
    return NULL;
}

int str_len(const char *str)
{
    if (*str)
        return 1 + str_len(str + 1);
    else
        return 0;
}

void mem_move(char *dst, const char *src, int len)
{
    int i;
    for (i = 0; i < len; i++)
        dst[i] = src[i];
}

int find_substring(FILE *f, const char *pattern)
{
    int res = 0;
    int pattern_len = str_len(pattern);
    int read_len;
    int tmp_buf_read = 1;
    char* tmp_buf = malloc(pattern_len * 2 - 1);
    char* buf = malloc(BUFLEN + 1);
    while ((read_len = fread(buf, sizeof(char), BUFLEN, f)) != 0) {
        buf[read_len] = 0;
        if (tmp_buf_read) {
            int len = read_len > pattern_len - 1 ? pattern_len - 1 : read_len;
            mem_move(tmp_buf, buf + read_len - len, len);
            tmp_buf[len] = 0;
        } else {
            int tmp_buf_len = str_len(tmp_buf);
            int len = read_len > pattern_len - 1 ? pattern_len - 1 : read_len;
            mem_move(tmp_buf + tmp_buf_len, buf, len);
            tmp_buf[len + tmp_buf_len] = 0;
            if (str_str(pattern, tmp_buf, pattern_len * 2 - 1))
                res++;
        }
        tmp_buf_read ^= 1;
        const char *tmp = buf;
        while ((tmp = str_str(pattern, tmp, read_len - (tmp - buf)))
                != NULL) {
            res++;
            tmp += pattern_len;
        }
    }
    if (ferror(f)) {
        fprintf(stderr, "error while reading file\n");
        perror("fread");
    }
    free(tmp_buf);
    free(buf);
    return res;
}

int main(int argc, const char** argv)
{
	if (argc < 3) {
		fprintf(stderr, "usage: <substring> <file>\n");
		return 1;
	}

	FILE *f;
    f = fopen(argv[2], "r");
	if (!f) {
		fprintf(stderr, "unable to open a file\n");
		perror("fopen");
		return 2;
	}
	int res = find_substring(f, argv[1]); 
	fclose(f);
    /*
        process arguments
        usage: [args] <pattern> [file]
        or
        usage: <pattern> [file] [args]

        open a main program with arguments and processing a pattern
        print string with pattern
    */
    /*
        open a file
        find substring in a file
        print count of matched substrings in a file
    */
    printf("%d\n", res);
    return 0;
}
