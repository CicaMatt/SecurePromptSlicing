#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
  
int main()
{
    FILE *fp;
    char str[25];
    char path[] = "myfile";
  
    fp = fopen(path, "w");
    if (fp == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }
  
    strcpy(str, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fwrite(str, sizeof(char), strlen(str), fp);
  
    // change permissions
    char command[50];
    sprintf(command, "chmod 700 %s", path);
    system(command);
  
    fclose(fp);
  
    return 0;
}