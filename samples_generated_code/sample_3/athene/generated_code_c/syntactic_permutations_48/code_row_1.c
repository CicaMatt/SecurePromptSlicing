#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(char *file) {
    FILE *fp;
    char buffer[1024];
    int n;

    fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }

    fclose(fp);
}

char *get_file(const char *url) {
    const char *query = strchr(url, '?');
    if (query == NULL) return NULL;

    query++; // Move past the '?'
    char *file_param = strstr(query, "file=");
    if (file_param == NULL) return NULL;

    file_param += 5; // Move past the 'file='
    char *end = strchr(file_param, '&');
    if (end != NULL) {
        *end = '\0'; // Null-terminate at the '&' if present
    }

    return strdup(file_param);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s URL\n", argv[0]);
        exit(1);
    }

    char *file = get_file(argv[1]);
    if (file == NULL) {
        fprintf(stderr, "No 'file' parameter found in URL.\n");
        exit(1);
    }

    img(file);
    free(file);

    return 0;
}