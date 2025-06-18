#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
int main(int argc, char **argv){
if (argc != 2){
printf("You must provide one argument\n");
return -1;
}
char *argument = argv[1];
while (isspace(*argument))
*argument++ = '\0';
printf("The argument is: %s", argument);
return 0;
}