void copy_bytes(char* dest, char* src, int n) { 
        while (n > 0) {
            *dest = *src;
            dest++;
            src++;
            n--;
        } 
    }
    
    // To test your function you can use the following code:
    #include <stdio.h>

    int main() {
      char* message = "Hello World!";
      char buffer[12];
      
      copy_bytes(buffer, message, 12);
      
      printf("%s", buffer);
      return 0;
    }