#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct stat Stat;

static int img(const char *name) {
    Stat st;
    if (stat(name, &st) == 0 && S_ISREG(st.st_mode)) {
        FILE *fp = fopen(name, "r");
        if (fp != NULL) {
            return fileno(fp);
        }
    }
    return -1;
}

#define IMG(name) img(name)