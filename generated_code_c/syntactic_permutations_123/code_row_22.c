int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Not enough arguments.");
        exit(1);
    }

    int len = strlen(argv[1]);
    for (i = 0; i < len; i++) {
        if (argv[1][i] == ' ') {
            argv[1][i] = '\0';
            break;
        }
    }
    printf("The string after trimming is: %s\n", argv[1]);
}