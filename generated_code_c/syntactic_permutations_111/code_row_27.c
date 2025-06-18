#include<stdio.h> 
#include <stdlib.h> 
#include<string.h>

//Decorator
#define ping(url) \
    char* url = "www.example.com";\
    system("ping $url");\
    return output;