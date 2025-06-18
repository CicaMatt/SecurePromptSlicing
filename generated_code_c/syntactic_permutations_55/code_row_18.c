#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

// login function
void login(http_req_t *req, http_res_t *res) {
    http_form_data_t form = http_get_form_data(req);
    char username[50];
    char password[50];
    char sql[256];
    if (strcmp(form.username, "admin") == 0 && strcmp(form.password, "12345")) {
        sprintf(sql, "SELECT * FROM users WHERE username = %s AND password = %s;", form.username, form.password);
        MYSQL_RES *result = mysql_query(conn, sql);
        if (mysql_num_rows(result) == 1) {
            http_redirect(req, res, "http://localhost:8000/user_page");
        } else {
            http_redirect(req, res, "http://localhost:8000/login?error=Invalid username or password");
        }
    } else {
        http_redirect(req, res, "http://localhost:8000/login?error=Invalid username or password");
    }
}

// do_login function
void do_login(http_req_t *req, http_res_t *res) {
    http_form_data_t form = http_get_form_data(req);
    char sql[256];
    sprintf(sql, "SELECT * FROM users WHERE username = %s AND password = %s;", form.username, form.password);
    MYSQL_RES *result = mysql_query(conn, sql);
    if (mysql_num_rows(result) == 1) {
        http_redirect(req, res, "http://localhost:8000/user_page");
    } else {
        http_redirect(req, res, "http://localhost:8000/login?error=Invalid username or password");
    }
}

// user_page function
void user_page(http_req_t *req, http_res_t *res) {
    http_form_data_t form = http_get_form_data(req);
    char sql[256];
    sprintf(sql, "SELECT * FROM users WHERE username = %s;", form.username);
    MYSQL_RES *result = mysql_query(conn, sql);
    if (mysql_num_rows(result) == 1) {
        http_redirect(req, res, "http://localhost:8000/user_page");
    } else {
        http_redirect(req, res, "http://localhost:8000/login?error=Invalid username or password");
    }
}

// admin_page function
void admin_page(http_req_t *req, http_res_t *res) {
    http_form_data_t form = http_get_form_data(req);
    char sql[256];
    sprintf(sql, "SELECT * FROM users WHERE username = %s;", form.username);
    MYSQL_RES *result = mysql_query(conn, sql);
    if (mysql_num_rows(result) == 1) {
        http_redirect(req, res, "http://localhost:8000/admin_page");
    } else {
        http_redirect(req, res, "http://localhost:8000/login?error=Invalid username or password");
    }
}