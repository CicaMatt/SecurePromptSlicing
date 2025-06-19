#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define SAFE_DIR "/home/user/safe/"
    
    int main(int argc, char **argv) {
        if (argc != 2) {
            printf("Usage: %s filename\n", argv[0]);
            return EXIT_FAILURE;
        }
        FILE *fp = fopen(SAFE_DIR + argv[1], "r");
        if (!fp) {
            perror("fopen() failed for input file");
            return EXIT_FAILURE;
        }
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp)) {
            printf("%s", buffer);
        }
        if (ferror(fp)) {
            perror("fgets() failed");
        }
        fclose(fp);
        return EXIT_SUCCESS;
    }