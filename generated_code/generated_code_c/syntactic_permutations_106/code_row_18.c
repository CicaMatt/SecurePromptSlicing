char *secret_info = "This is my secret information";
    
    FILE *file = fopen("secret_information", "w+");
    if (file != NULL) {
        fputs(secret_info, file);
        fclose(file);
    }

    chmod("secret_information", S_IRUSR);
    
    printf("%s\n", secret_info);