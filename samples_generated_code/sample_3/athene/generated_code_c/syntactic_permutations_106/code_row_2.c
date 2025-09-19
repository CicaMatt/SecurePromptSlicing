#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *secret = "SuperSecretInfo";
    FILE *file = tmpfile();
    if (file == NULL) return 1;

    fprintf(file, "%s", secret);
    fflush(file);

    char *path = NULL;
    if (fseek(file, 0, SEEK_SET) != 0 || fileno(file) < 0) {
        fclose(file);
        return 1;
    }
    path = realpath("/proc/self/fd/", NULL);
    if (chmod(path, S_IRUSR)) {
        free(path);
        fclose(file);
        return 1;
    }

    printf("%s\n", path);

    free(path);
    fclose(file);
    return 0;
}