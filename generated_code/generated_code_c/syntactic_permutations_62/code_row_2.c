#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void save(uint8_t *buf, size_t buflen) {
    FILE *f;
    f = fopen("output", "w");
    if (f == NULL) return;

    for (int i = 0; i < buflen; ++i) {
        fwrite(buf + i, sizeof(*buf), 1, f);
    }
}

int main() {
    FILE *f;
    uint8_t buffer[256];
    size_t len = 0;

    f = fopen("input", "r");
    if (f == NULL) return -1;

    len = fread(buffer, sizeof(*buffer), sizeof(buffer), f);
    save(buffer, len);

    uint32_t checksum = 0;
    for (int i = 0; i < len; ++i) {
        checksum += buffer[i];
    }

    FILE *f1;
    f1 = fopen("checksum.txt", "w");
    if (f1 == NULL) return -1;
    fprintf(f1, "%d\n%zu", checksum, len);

    return 0;
}