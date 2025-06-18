#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(0)); // seed random with current time
    float f1 = (float)rand() / RAND_MAX; // generate a random float between 0 and 1
    float f2 = (float)rand() / RAND_MAX;
    float f3 = (float)rand() / RAND_MAX;

    char str1[5];
    sprintf(str1, "%f", f1);
    char str2[5];
    sprintf(str2, "%f", f2);
    char str3[5];
    sprintf(str3, "%f", f3);

    FILE *fp;
    fp = fopen("output.txt", "w+"); // create and open a file for writing
    if (!fp) {
        printf("Error creating output file\n");
        return 1; // return an error code
    }
    char str[30] = ""; // initialize string buffer
    strcat(str, str1); // concatenate the float strings
    strcat(str, " "); // add a space between them
    strcat(str, str2);
    strcat(str, " ");
    strcat(str, str3);

    fprintf(fp, "%s", str); // write the string to file
    fclose(fp); // close file when done

    printf("Wrote %s\n", str); // print success message and exit
    return 0;
}