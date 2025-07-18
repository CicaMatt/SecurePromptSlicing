#include <stdio.h>
#include <string.h>
int main() {
    char buffer[256];
    char filename[32];
    unsigned short int checksum = 0;
    unsigned long int bytesRead = 0;
    printf("Enter the name of a file to open: ");
    scanf("%s", filename);
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
    } else {
        bytesRead = fread(buffer, 1, sizeof(buffer), fp);
        for (int i=0; i<bytesRead; i++) {
            checksum += buffer[i];
        }
        printf("Checksum of %s is: %d", filename, checksum);
    }
    fclose(fp);
    FILE* sumFile = fopen("checksum.dat", "w");
    fprintf(sumFile, "%ld\n%d", bytesRead, checksum);
    fclose(sumFile);
}