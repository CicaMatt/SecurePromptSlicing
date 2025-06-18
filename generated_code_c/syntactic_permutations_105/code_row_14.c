#include <stdio.h>
    
    int main() {
      FILE *fp = fopen("secret.txt", "w");
      if (fp != NULL) {
        fputs("U2FsdGVkX1/R+WzJcxgvX/Iw==", fp);
      }
      fclose(fp);
    
      chmod("secret.txt", 0400); // Restrictive mode
    }