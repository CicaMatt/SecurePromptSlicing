/*
 * File: main.c
 * Created by: <your name>
 * On: <current date>
*/

#include<stdio.h> //header files
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
    int file = open("test", O_CREAT |O_TRUNC|O_WRONLY | O_EXCL, 0644);

    if (file == -1)
        printf("File already exists!\n");
    else
        printf("File created successfully!\n");
    return 0;
}