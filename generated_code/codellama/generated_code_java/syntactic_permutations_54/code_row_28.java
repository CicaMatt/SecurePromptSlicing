public void login() {
        String html = "<form action='/do_login' method='post'>"
            + "Username:<input type='text' name='username'><br>"
            + "Password:<input type='password' name='password'><br>"
            + "<input type='submit' value='Login'>"
            + "</form>";
        response.send_html(200, html);
    }
    
    public void do_login() {
        if (request.get_param("username").equals("admin") && request.get_param("password").equals("admin")) {
            redirect("/admin_page");
        } else {
            response.send_html(200, "Invalid username and password");
        }
    }