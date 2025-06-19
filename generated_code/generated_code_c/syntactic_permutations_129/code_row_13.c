#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "render_response_from_env.h"

int main(void){
    char name[256];
    printf("Enter your name: ");
    scanf("%s",name);
    
    render_response_from_env(name,getenv("REQUEST_METHOD"),getenv("QUERY_STRING"));
   return 0;
}