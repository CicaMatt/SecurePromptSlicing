#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    
    void trim(char* s) {
      char* p = s;
      int l = strlen(p);
      
      while (l > 0 && p[l - 1] == '\n') p[--l] = 0;
      
      while (l > 0 && p[l - 1] == ' ') p[--l] = 0;
    }
    
    void main(int argc, char *argv[]){
      if(argc != 2) {
        printf("error: missing program name\n");
        exit(1);
      }
      
      char* pname = argv[0];
      
      int l = strlen(pname);
      
      while (l > 0 && pname[l - 1] == '\n') {
        pname[--l] = 0;
      }
      
      printf("%s\n", pname);
    }