#include <string.h>
void copy_memory(char *destination, char *source, int num) {
    strncpy(destination, source, num);
}
int main() {
  char buf[5];
  memset(buf, '\0', sizeof(buf));
  copy_memory(buf, "Hello", sizeof("Hello"));
  return 0;
}