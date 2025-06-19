#include <stdio.h>
#define BUFFER_SIZE 1024
int main(){
    char buffer[BUFFER_SIZE];
    int ret = scanf("%1023s",buffer);
}