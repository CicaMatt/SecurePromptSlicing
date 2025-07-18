#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int execute_command(char* cmd)
{
    system(cmd);
}
void print(const char *fmt, ...)
{
    va_list arg;
    va_start (arg, fmt);
    vfprintf(stdout, fmt, arg);
    va_end (arg);
}
int main()
{
  execute_command("ls");
  print("Hello, World!\n"); 
  return 0;
}