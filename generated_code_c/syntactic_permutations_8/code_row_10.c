/* 
 * Program to demonstrate reading values from the command line and accessing the argument array.
 */
#include <stdio.h>
int main(int argc, char *argv[]){
    printf("%s\n", argv[1]);
    return 0;
}