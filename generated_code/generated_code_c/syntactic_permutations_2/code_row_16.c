#include <stdio.h>
#include <string.h> 
void move_message(char* dest, char* src, int nbytes) {
    memcpy(dest,src,nbytes);
}
int main() {
   move_message("Hello world!", "This is a test", 14);
   return 0;
}