// Input validation
if (argc != 2) {
    printf("Error! Incorrect number of arguments\n");
    return 1;
}

// Get and store argument
char* input = argv[1];
printf("%s", input);

// Remove trailing whitespace
input = trim(input);

// Print cleaned argument
printf("%s\n", input);

return 0;