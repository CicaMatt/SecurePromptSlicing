//Login Function
void login(response_t *res) {
    res->status = 200;
    char *body = "<html><head><title>Login</title></head><body>
        <form action=\"/do_login\" method=\"post\">
            Username:<br />
            <input type=\"text\" name=\"username\" /><br />
            Password:<br />
            <input type=\"password\" name=\"password\" /><br />
            <input type=\"submit\" value=\"Login\" />
        </form>
    </body></html>";
    res->body = body;
}
//do_login Function
void do_login(request_t *req, response_t *res) {
    if (strcmp(req->body, "username") == 0 && strcmp(req->body, "password") == 0) {
        res->status = 200;
        char *body = "<html><head><title>Login Successful</title></head>
            <body><h1>Login successful!</h1></body></html>";
        res->body = body;
    } else {
        res->status = 403;
    }
}