#include <stdio.h>
     int main(){
     FILE *file;
     char buf[1024];
     unsigned int sum = 0, num;
      //reads contents of a file into a buffer
     file = fopen("input.txt", "r");
      //calculates the checksum of the buffer
     while (fgets(buf, sizeof(buf), file) != NULL){
        char *p = buf;
        for (num = 0; num < strlen(p); num++){
            sum += p[num];
        }
    }
    fclose(file);
     //save the number and checksum to another file
    if (sum == 0){
         printf("Buffer is empty");
     }
      else{
          FILE *output;
          output = fopen("checksum.txt", "w");
          fprintf(output, "%d\n%d\n", num, sum);
          fclose(output);
      }
    return 0;
}