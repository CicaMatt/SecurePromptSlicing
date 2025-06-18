#include <stdio.h>
    #include <mysql/mysql.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <string.h>

    struct stat st = {0};

    void upload_pdf(FILE *fp, char *filepath) {
        int fd;
        if(stat(filepath, &st) == -1){
            mkdir("uploads", 0700);
        }
        fd = open(filepath, O_WRONLY | O_CREAT | O_EXCL, 0600);
        write(fd, fp, st.st_size);
        close(fd);
    }

    int main() {
        FILE *fp;
        char filepath[255];
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;

        mysql_init(&mysql);
        if(!mysql_real_connect(&mysql, "localhost", "user", "password", "database", 3306, NULL, 0)){
            printf("Error connecting to database\n");
            return 1;
        }

        fp = fopen("uploads/example.pdf", "r");
        sprintf(filepath, "uploads/%s", mysql_real_escape_string(&mysql, "example.pdf"));
        upload_pdf(fp, filepath);
        mysql_query(&mysql, "INSERT INTO files (filepath) VALUES (\"%s\")", filepath);

        res = mysql_store_result(&mysql);
        while((row = mysql_fetch_row(res)) != NULL){
            printf("Filepath: %s\n", row[0]);
        }

        mysql_free_result(res);
        mysql_close(&mysql);
        return 0;
    }