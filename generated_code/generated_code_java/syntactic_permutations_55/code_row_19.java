import java.io.*;
    
    // First function: login()
    public String login() {
        return "GET /login HTTP/1.1\r\n" +
                "Host: 127.0.0.1:5000\r\n" +
                "Connection: keep-alive\r\n" +
                "\r\n";
    }
    
    // Second function: do_login()
    public String do_login(String username, String password) {
        return "POST /login HTTP/1.1\r\n" +
                "Host: 127.0.0.1:5000\r\n" +
                "Content-Type: application/x-www-form-urlencoded\r\n" +
                "Content-Length: 39\r\n" +
                "\r\n" +
                "username=" + username + "&password=" + password;
    }
    
    // Third function: user_page()
    public String user_page() {
        return "GET /user/page HTTP/1.1\r\n" +
                "Host: 127.0.0.1:5000\r\n" +
                "Connection: keep-alive\r\n" +
                "\r\n";
    }
    
    // Fourth function: admin_page()
    public String admin_page() {
        return "GET /admin/page HTTP/1.1\r\n" +
                "Host: 127.0.0.1:5000\r\n" +
                "Connection: keep-alive\r\n" +
                "\r\n";
    }