// Login function
    void login(http_request *request) {
        http_response *response = request->response;
        response->setHeader("Content-Type", "text/html");
        response->write("<form method='post'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><button type='submit'>Log In</button></form>");
    }

    // Do login function
    void do_login(http_request *request) {
        http_response *response = request->response;
        string username = request->getParameter("username");
        string password = request->getParameter("password");
        if (username == "admin" && password == "admin") {
            response->redirect("/admin_page");
        } else {
            response->write("<h1>Invalid username or password</h1>");
        }
    }