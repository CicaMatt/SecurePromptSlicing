#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "tarfile.h"
 
int main(void) {
    char *tmp = getenv("TMPDIR");
    if (tmp == NULL || strlen(tmp) == 0) {
        tmp = "/tmp";
    }
    strcat(tmp, "/unpack");
    int status = mkdir(tmp, S_IRWXU);
    if (status != 0) {
        perror("mkdir failed");
        exit(1);
    }
    char *tarball = "archive.tar.gz";
    TarFile *tf = tarfile_open(tarball, NULL);
    if (tf == NULL) {
        fprintf(stderr, "cannot open tar archive '%s'\n", tarball);
        exit(1);
    }
    char *member;
    while ((member = tarfile_next(tf)) != NULL) {
        char path[PATH_MAX];
        strcpy(path, tmp);
        strcat(path, "/");
        strcat(path, member);
        FILE *f = fopen(path, "wb");
        if (f == NULL) {
            perror("cannot open output file");
            exit(1);
        }
        int status = tarfile_extractfile(tf, member, f);
        if (status != 0) {
            fprintf(stderr, "cannot extract file '%s' from archive\n", member);
            exit(1);
        }
        fclose(f);
    }
    tarfile_close(tf);
    return 0;
}