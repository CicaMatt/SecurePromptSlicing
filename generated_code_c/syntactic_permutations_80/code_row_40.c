#include <stdio.h>
#define MAX_LEN 1024
int main(void) {
   char str[MAX_LEN];
   scanf("%1023s", str);
   printf("Your string is: %s\n", str);
   return 0;
}