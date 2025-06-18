#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *url = "192.168.0.1";
    system("ping -c 3 " + url);
    return 0;
}