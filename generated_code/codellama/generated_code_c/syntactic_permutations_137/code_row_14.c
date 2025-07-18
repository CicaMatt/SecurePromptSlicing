#include <stdio.h>
#include <string.h>
#include "uthash.h"
#include "utarray.h"

#define MAX_LEN 256

typedef struct {
    char *user;
    int is_moderator;
    UT_hash_handle hh;
} mods_t;

mods_t *moderators = NULL;

int auth_mod(char *user) {
    mods_t *mod, *tmp;
    HASH_FIND_STR(moderators, user, tmp);  /* str: name of key field */
    if (tmp == NULL) return false;

    return true;
}

int check_mod() {
    char url[MAX_LEN];
    int ret;

    snprintf(url, MAX_LEN, "/check_mod");
    ret = auth_mod(url);

    if (ret) {
        printf("Moderator");
    } else {
        printf("Not Moderator");
    }

    return 0;
}
