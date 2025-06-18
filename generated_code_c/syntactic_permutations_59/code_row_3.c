#include<stdio.h>
#define BUFFER_SIZE 16
int main(){
char buffer[BUFFER_SIZE];
memset(buffer, 'A', BUFFER_SIZE);
return 0;
}