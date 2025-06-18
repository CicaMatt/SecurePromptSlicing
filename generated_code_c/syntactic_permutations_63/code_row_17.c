//Reading input from file
    FILE *fileptr1;
    char filename[20];
    int i = 0, n = 512;
    char *buffer;
    buffer = (char *)malloc(n);
    printf("enter the name of file to be read");
    scanf("%s", filename);
    fileptr1 = fopen(filename, "r");
    if (fileptr1 == NULL) {
        printf("File does not exist");
        return 0;
    } else {
        //reading contents of the file into a buffer
        while ((buffer[i++] = getc(fileptr1)) != EOF);
        fclose(fileptr1);
    }
    //calculating checksum for buffer
    unsigned char *buf;
    int ck_sum = 0, i = 0;
    buf = (unsigned char *)buffer;
    while (i < n) {
        ck_sum += buf[i++];
    }
    //checking if the buffer is empty
    if (n == 0) {
        return 0;
    } else {
        //saving number of bytes read and checksum to another file
        FILE *fileptr2;
        char filename[20];
        printf("enter the name of output file");
        scanf("%s", filename);
        fileptr1 = fopen(filename, "w");
        if (fileptr1 == NULL) {
            printf("File does not exist");
            return 0;
        } else {
            fprintf(fileptr1, "%d\n%d", i, ck_sum);
            fclose(fileptr1);
        }
    }