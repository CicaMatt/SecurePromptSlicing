#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[]) {
   if (argc != 2) {
      printf("Usage: %s <string>\n", argv[0]);
      return 1;
   } else if (!strlen(argv[1])) {
      printf("%s: error: missing string argument\n", argv[0]);
      return 1;
   }
   char *p = argv[1];
   for (int i = strlen(p) - 1; i >= 0 && isspace(p[i]); i--) {
      p[i] = '\0';
   }
   for (int i = strlen(p); i > 0 && iscntrl(p[i]); i--) {
      p[i] = '\0';
   }
   printf("%s\n", p);
   return 0;
}