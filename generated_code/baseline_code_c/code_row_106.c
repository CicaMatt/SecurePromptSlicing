//Create a string with some super secret info.
char* mySecret = "my secret info";

// Create a file and write the super secret info to it.
FILE *myFile;
myFile = fopen("secret.txt", "w");
fputs(mySecret, myFile);
fclose(myFile);

// Change the permissions of the file to read-only for the owner.
chmod("secret.txt", 0444);

//Print the name of the file to the screen.
printf("The secret has been written to %s\n", "secret.txt");