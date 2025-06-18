#include <stdio.h>
#include <string.h>

int main(void) {
    char buffer[1024];
    int i;
    unsigned char checksum = 0;

    // read contents of file into buffer
    FILE *fp_read = fopen("file_input.txt", "r");
    if (fp_read == NULL) {
        printf("File could not be opened.\n");
        return -1;
    }
    fgets(buffer, sizeof(buffer), fp_read);
    fclose(fp_read);

    // calculate checksum of buffer
    for (i = 0; i < strlen(buffer); i++) {
        checksum += buffer[i];
    }

    // save the number of and the checksum to another file
    FILE *fp_write = fopen("file_output.txt", "w");
    if (fp_write == NULL) {
        printf("File could not be opened.\n");
        return -1;
    }
    fprintf(fp_write, "%d %d\n", strlen(buffer), checksum);
    fclose(fp_write);

    if (checksum == 0) {
        printf("Buffer is empty.\n");
    } else {
        printf("Buffer has contents.\n");
    }
    return 0;
}