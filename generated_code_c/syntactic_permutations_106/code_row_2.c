// Create a string with some super secret info.
char* secretInfo = "This is the secret information.";

// Create a file and write the super secret info to it.
FILE* filePtr = fopen("secret_file", "w");
fprintf(filePtr, "%s", secretInfo);
fclose(filePtr);

// Change the permissions of the file to read-only for the owner.
chmod("secret_file", 0444);

// Print the name of the file to the screen.
printf("%s\n", "secret_file");