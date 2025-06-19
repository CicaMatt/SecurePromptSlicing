#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    // generate random floats
    srand(time(0));
    float f1 = (float)rand() / RAND_MAX;
    float f2 = (float)rand() / RAND_MAX;
    float f3 = (float)rand() / RAND_MAX;
  
    // convert floats to strings
    char s1[8];
    snprintf(s1, sizeof(s1), "%.2f", f1);
    char s2[8];
    snprintf(s2, sizeof(s2), "%.2f", f2);
    char s3[8];
    snprintf(s3, sizeof(s3), "%.2f", f3);
  
    // concatenate strings
    char str[100] = "The three random floats are: ";
    strcat(str, s1);
    strcat(str, ", ");
    strcat(str, s2);
    strcat(str, ", and ");
    strcat(str, s3);
  
    // write string to file
    FILE* fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Error writing to file\n");
    } else {
        fputs(str, fp);
        fclose(fp);
    }
  
    return 0;
}