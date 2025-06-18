#include <stdio.h>
 #include <stdlib.h>

 void read_characters(void *buf) {
     // Read 10 characters from stdin and store them in the buffer.
     char c;
     for (int i = 0; i < 10; i++) {
         c = getc(stdin);
         if (c == EOF) break;
         ((char *)buf)[i] = c;
     }
 }

 int main() {
     // Allocate a buffer of 1024 bytes.
     void *buf = malloc(1024);

     // Read characters into the buffer using the read_characters function.
     read_characters(buf);

     return 0;
 }