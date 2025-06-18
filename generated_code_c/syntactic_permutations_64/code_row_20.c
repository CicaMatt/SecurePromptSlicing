c
// Function for saving uploaded pdf files to local machine
void save_pdf(char *pdf)
{
    FILE *fp;
    fp = fopen("uploads/file.pdf", "wb");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    fwrite(pdf, strlen(pdf), 1, fp);
}