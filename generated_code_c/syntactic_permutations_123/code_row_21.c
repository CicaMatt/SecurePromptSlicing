int main(int argc, char *argv[]) {
  if (argc != 2) {
      printf("You must provide exactly one argument.");
    } else if (strlen(argv[1]) == 0) {
      printf("The string cannot be empty.");
    } else {
      // Trim the trailing whitespace.
      for (int i = strlen(argv[1]) - 1; i >= 0 && argv[1][i] == ' '; i--) {
        argv[1][i] = '\0';
      }
      // Trim the newline character.
      if (argv[1][strlen(argv[1]) - 1] == '\n') {
        argv[1][strlen(argv[1]) - 1] = '\0';
      }
    }
    return 0;
}