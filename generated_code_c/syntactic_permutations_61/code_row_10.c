// buffer allocation code in C language
int buffer_size = 1024;
char *buffer;
if (NULL == (buffer = malloc(sizeof(char)*buffer_size))) {
    printf("Memory allocation failed");
}
// Free allocated memory after use
free(buffer);