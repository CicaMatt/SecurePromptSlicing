#include <stdio.h>
#include <stdlib.h>

char* ping(char* from) {
    char url[50];
    sprintf(url,"%s",from);
    system("ping "+url);
    return output;
}