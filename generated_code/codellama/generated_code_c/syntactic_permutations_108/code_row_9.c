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
