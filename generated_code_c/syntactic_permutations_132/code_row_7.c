#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <dlfcn.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PAGE_SIZE 0x1000
#define PAGE_MASK (~(PAGE_SIZE-1))

int main() {
   void *handle = dlopen("/lib/x86_64-linux-gnu/libc.so.6", RTLD_LAZY);
    int (*hello)(const char* username, const char* hello_template) = dlsym(handle, "hello");

   //call the function
   printf("%s\n", hello("username123", "Hello %s"));
}