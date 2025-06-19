#include <stdio.h>
#include <stdlib.h>
#define DEF_URL "www.google.com"
typedef struct {
    char *url;
}ping_args;
void ping(ping_args args){
    if (system("ping -c 100 " args->url) == -1) {
        perror("Can't run command");
        exit(EXIT_FAILURE);
    } else {
        puts(args->url);
        exit(EXIT_SUCCESS);
    }
}
int main(){
    ping_args *p_args = malloc(sizeof(*p_args));
    p_args->url = DEF_URL;
    ping(p_args);
    return 0;
}