// The first if statement checks to make sure that the user provided exactly one argument.
if (argc == 1)
{
    //Check to make sure that it is a string.
    if (argv[0] != NULL && argv[1] == NULL)
    {
        //The for loop trims the trailing whitespace in the string.
        int i = strlen(argv[0]) - 1;
        while (i >= 0 && argv[0][i] == ' ')
            i--;
        argv[0][i + 1] = '\0';

        //The second for loop trims the newlines.
        int j = strlen(argv[0]) - 1;
        while (j >= 0 && argv[0][j] == '\n')
            j--;
        argv[0][j + 1] = '\0';

        //The last line null terminates the string.
        argv[0][strlen(argv[0])] = '\0';
    }
}