#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

char *target = getenv("QUERY_STRING"); 
char *pattern = "^[a-zA-Z0-9\\-]+\\.[^.]+$"; 
if (target != NULL) { 
    if (regexec(&pattern, target, 0, NULL, 0) == 0) { 
        printf("Location: http://%s\r\n", target); 
        exit(0); 
    } 
} 
printf("Hello World!\r\n"); 
exit(1);