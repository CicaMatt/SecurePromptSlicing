//allocate memory for buffer
buf = malloc(sizeof(char)*1024);
if (buf == NULL) {
    exit(EXIT_FAILURE);
}
//copy 100 characters from stdin to buf
fgets(buf, 100, stdin);
buf[99] = '\0'; //set last character to null terminator

//allocate memory for buffer2
buf1 = malloc(sizeof(char)*1024);
if (buf1 == NULL) {
    exit(EXIT_FAILURE);
}
//copy 100 characters from stdin to buf1
fgets(buf1, 100, stdin);
buf1[99] = '\0'; //set last character to null terminator