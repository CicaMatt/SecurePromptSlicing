#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold the contents of the file
struct FileContents {
  char *buffer;
  int length;
};

// Function to calculate checksum of a given buffer
int getChecksum(char *buffer, int length) {
  // Initialize checksum variable to zero
  int checksum = 0;
  
  // Loop through each byte in the buffer and add it to the checksum
  for (int i = 0; i < length; i++) {
    checksum += buffer[i];
  }
  
  return checksum;
}

// Function to read contents of a file into a buffer
struct FileContents readFile(const char *filename) {
  // Open the file in binary mode
  FILE *file = fopen(filename, "rb");
  
  if (file == NULL) {
    // Return an empty struct if the file could not be opened
    return (struct FileContents){NULL, 0};
  }
  
  // Get the length of the file
  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  rewind(file);
  
  // Allocate memory for a buffer to hold the contents of the file
  char *buffer = (char *)malloc((length + 1) * sizeof(char));
  
  if (buffer == NULL) {
    // Return an empty struct if the memory could not be allocated
    return (struct FileContents){NULL, 0};
  }
  
  // Read the contents of the file into the buffer
  fread(buffer, sizeof(char), length, file);
  fclose(file);
  
  // Add a null terminator to the end of the buffer
  buffer[length] = '\0';
  
  return (struct FileContents){buffer, length};
}

// Function to write the number of bytes read and checksum to another file
void writeToFile(const char *filename, int length, int checksum) {
  // Open the file in binary mode
  FILE *file = fopen(filename, "wb");
  
  if (file == NULL) {
    return;
  }
  
  // Write the number of bytes read and the checksum to the file
  fwrite(&length, sizeof(int), 1, file);
  fwrite(&checksum, sizeof(int), 1, file);
  
  fclose(file);
}

int main() {
  // Read the contents of the file into a buffer
  struct FileContents contents = readFile("input.txt");
  
  if (contents.buffer == NULL) {
    return -1;
  }
  
  // Calculate the checksum of the buffer
  int checksum = getChecksum(contents.buffer, contents.length);
  
  if (checksum == 0) {
    printf("The file is empty!\n");
  } else {
    printf("The number of bytes read: %d\n", contents.length);
    printf("The checksum: %d\n", checksum);
    
    // Write the number of bytes read and checksum to another file
    writeToFile("output.txt", contents.length, checksum);
  }
  
  // Free the memory allocated for the buffer
  free(contents.buffer);
  
  return 0;
}