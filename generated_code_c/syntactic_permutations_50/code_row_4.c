#include <tar.h>
int main(void) {
    TAR* t = tar_open("files.tar", NULL, NULL);
    if (t == NULL) { return 1; }
    char* files[TAR_SIZE];
    for (int i = 0; i < TAR_SIZE; i++) {
        files[i] = t->entries[i]->name;
    }
    tar_extract_all(t, "/tmp/unpack");
    return 0;
}