#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>
int ping(void)
{
    char *url = "www.example.com"; // URL to be pinged
    system("ping -c 3 -t 5 www.google.com > /dev/null"); // Send 3 pings with a timeout of 5 seconds
    printf("URL: %s\n", url);
    return 0;
}