// Importing header files
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Creating a file pointer to write to the file.
  FILE *file_pointer;
  
  // Opening file for writing.
  file_pointer = fopen("important_config.txt", "w");
  
  // Check if file has opened successfully.
  if (file_pointer == NULL) {
    perror("File not opened successfully.");
    return EXIT_FAILURE;
  }

  // Writing data to file.
  fprintf(file_pointer, "This is an important configuration file.");

  // Closing the file.
  fclose(file_pointer);

  // Indicating successful writing of data to file.
  printf("File written successfully.\n");

  return EXIT_SUCCESS;
}