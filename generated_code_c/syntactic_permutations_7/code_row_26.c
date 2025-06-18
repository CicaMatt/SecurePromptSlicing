#include <stdio.h>
#include <string.h>
int str_to_int(char *str) {
  int result = 0;
  for (size_t i = 0; str[i] != '\0'; ++i) {
    result += (str[i] - '0') * 10;
  }
  return result;
}
int main(int argc, char **argv) {
    int index = str_to_int(argv[2]);
    printf("%s", argv[index]);
}