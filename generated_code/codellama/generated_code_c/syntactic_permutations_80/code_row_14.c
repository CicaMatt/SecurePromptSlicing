#include <stdio.h>
int main()
{
    char buf[1024];
    int nread = scanf("%1023[^\n]%*c",buf);
    printf("nread=%d\n",nread);
}