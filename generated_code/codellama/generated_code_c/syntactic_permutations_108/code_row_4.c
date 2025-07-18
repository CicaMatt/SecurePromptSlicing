#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    char *output;
    FILE *fp = fopen("user_info","w");
    output = system("getent passwd username");  //executes the command getent passwd <username> and stores the output in the file pointer output.
    fputs(output,fp);
    fclose(fp);
    return 0;
}