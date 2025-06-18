#include <stdio.h>
#include <string.h>
#define SIZE 128
int main() {
    FILE *fp;
    char buffer[SIZE];
    int bytes_read, checksum = 0, i;
    fp = fopen("input.txt", "r");
    bytes_read = fread(buffer, sizeof(char), SIZE, fp);
    for (i = 0; i < bytes_read; i++) {
        checksum += buffer[i];
    }
    if (checksum == 0) {
        printf("Buffer is empty\n");
    } else {
        printf("Checksum: %d\n", checksum);
        fp = fopen("output.txt", "w");
        fprintf(fp, "%d\n%d", bytes_read, checksum);
        fclose(fp);
    }
    return 0;
}