#include <stdio.h>
int main(){
char command[100];
sprintf(command, "ls -l");
system(command);
return 0;
}