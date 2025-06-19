// Importing necessary libraries
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Check the number of arguments passed
  if (argc != 2) {
    printf("Usage: ./program <image file>\n");
    exit(1);
  }

  // Storing the filename in a variable
  const char *filename = argv[1];

  // Opening the image file using fopen() function
  FILE *img_file = fopen(filename, "rb");
  if (img_file == NULL) {
    printf("Unable to open image file\n");
    exit(1);
  }

  // Determining the size of the file using fseek() and ftell()
  fseek(img_file, 0L, SEEK_END);
  long int size = ftell(img_file);
  fseek(img_file, 0L, SEEK_SET);

  // Allocating memory to store the contents of the file
  char *buffer = (char *)malloc(size + 1);
  if (buffer == NULL) {
    printf("Unable to allocate buffer\n");
    exit(1);
  }

  // Reading the file into the memory buffer
  fread(buffer, size, 1, img_file);
  fclose(img_file);

  // Storing the buffer in a variable
  const char *image = buffer;

  // Printing the image to the console
  printf("%s", image);

  // Freeing up memory allocated for the buffer
  free(buffer);

  return 0;
}