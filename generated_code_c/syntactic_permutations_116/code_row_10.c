#include <stdio.h>  //for printf()
#include <stdlib.h> //for system()
int main() {
    system(printf("ls -l"));//system() runs the ls command in the shell
    return 0;
}