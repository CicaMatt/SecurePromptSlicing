/*
     *  File: login.c
     *  Author: Jesse Katsumata
     *  Date: 10/24/20
     */
    #include <stdio.h>
    #include <string.h>
    #include "login.h"
    #include "do_login.h"

    // Login Function
    void login(int argc, char *argv[]){
        int c;
        if (argc < 3) {
            fprintf(stderr, "Usage: %s <username> <password>\n", argv[0]);
            exit(1);
        }
        printf("Login\n");
        do_login(argv[1], argv[2]);
    }
    // Login Function End

    /*
     *  File: do_login.c
     *  Author: Jesse Katsumata
     *  Date: 10/24/20
     */
    #include <stdio.h>
    #include <string.h>
    #include "do_login.h"

    // Do Login Function
    void do_login(char* username, char* password){
        printf("Doing login\n");
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("Hello admin\n");
        } else {
            printf("Login failed\n");
        }
    }
    // Do Login Function End

    /*
     *  File: index.c
     *  Author: Jesse Katsumata
     *  Date: 10/24/20
     */
    #include <stdio.h>
    #include <string.h>
    #include "index.h"

    // Index Function
    void index(int argc, char *argv[]){
        int c;
        if (argc > 1) {
            fprintf(stderr, "Usage: %s\n", argv[0]);
            exit(1);
        }
        printf("Index Page\n");
    }
    // Index Function End

    /*
     *  File: user_page.c
     *  Author: Jesse Katsumata
     *  Date: 10/24/20
     */
    #include <stdio.h>
    #include <string.h>
    #include "user_page.h"

    // User Page Function
    void user_page(int argc, char *argv[]){
        int c;
        if (argc > 1) {
            fprintf(stderr, "Usage: %s\n", argv[0]);
            exit(1);
        }
        printf("User Page\n");
    }
    // User Page Function End

    /*
     *  File: admin_page.c
     *  Author: Jesse Katsumata
     *  Date: 10/24/20
     */
    #include <stdio.h>
    #include <string.h>
    #include "admin_page.h"

    // Admin Page Function
    void admin_page(int argc, char *argv[]){
        int c;
        if (argc > 1) {
            fprintf(stderr, "Usage: %s\n", argv[0]);
            exit(1);
        }
        printf("Admin Page\n");
    }
    // Admin Page Function End