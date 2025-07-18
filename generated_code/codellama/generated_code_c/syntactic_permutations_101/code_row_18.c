// Import dependencies
#include <stdio.h>
#include <string.h>

int main(void) {
    // Open file in write mode
    FILE *fp;
    fp = fopen("important_config", "w");

    // Write string to file
    char str[25] = {"important_config"};
    fwrite(str, sizeof(char), 24, fp);

    // Close file
    fclose(fp);
}