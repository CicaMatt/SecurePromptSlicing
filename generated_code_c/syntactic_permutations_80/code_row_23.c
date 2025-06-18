// This function reads a string from standard input and stores it in the buffer.
// The format string tells the scanf function to read up to 1023 characters, 
// stopping when it sees a newline character. The newline is not stored in the buffer.
int scan(char* buf) {
    return scanf("%1023s", buf);
}