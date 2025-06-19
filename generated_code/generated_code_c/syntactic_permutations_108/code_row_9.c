#include<stdio.h>
 #include<stdlib.h>
 
 int main()
 {
    char *user = "sophia";
    FILE *output;
    output = popen("getent passwd sophia", "r");
    if (output == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }
    char buffer[128];
    while(fgets(buffer, sizeof(buffer), output) != NULL)
    {
        printf("%s", buffer);
    }
    pclose(output);
    return 0;
 }

### Explanation:
In this program we have included the header files stdio.h and stdlib.h. In main() function, firstly user is assigned sophia. Then output file pointer is generated using popen() function which executes getent passwd <username> command. 
The while loop is used to store the output in buffer variable till it reaches end of file. The printf() is used to print the buffer data. pclose() function closes the process and returns the exit status of the command as an integer.