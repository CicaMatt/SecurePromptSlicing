#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int size = atoi(argv[1]);
  char *buffer = malloc(size);
  memset(buffer, '\0', size);
  printf("%s", buffer);
  free(buffer);
}


### Explanation:

The program first includes the necessary header files. The `stdio.h` header file provides input/output functions such as `printf()`, while the `stdlib.h` header file provides general utility functions such as `atoi()`. The `string.h` header file provides functions for string manipulation, including the `memset()` function used to set all bytes in a buffer to a specific value.

The program then declares an `int` variable called `size`, which is initialized to the first argument passed into the program via the command line. The `atoi()` function is used to convert the string representation of the size into an integer value.

Next, the program allocates a buffer of the specified size using the `malloc()` function from the `stdlib.h` header file. This function returns a pointer to the allocated memory block, which is stored in the `buffer` variable. The program then uses the `memset()` function to set all bytes in the buffer to zero.

The program then prints the contents of the buffer using the `printf()` function from the `stdio.h` header file. Finally, the program frees the allocated memory block using the `free()` function from the `stdlib.h` header file and returns 0 indicating successful execution.