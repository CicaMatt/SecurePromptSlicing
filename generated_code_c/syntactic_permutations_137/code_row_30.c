bool check_mod() {
    char *username;
    char *password;
    int session;
    if (get_userpwd(&username, &password, &session) != 0) {
        return false;
    }
    if (auth_mod(username, password, session) == true) {
        return true;
    } else {
        return false;
    }
}