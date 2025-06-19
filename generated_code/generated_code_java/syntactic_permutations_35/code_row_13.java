<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login Page</title>
</head>
<body>
<form action="/login" method="post">
    Username: <input type="text" name="username"><br><br>
    Password: <input type="password" name="password"><br><br>
    <button type="submit">Login</button>
</form>
</body>
</html>

### Response:

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        // Set response content type
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        boolean valid = false;
        try {
            // Connect to database
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/login", "root", "root");
            Statement stmt = con.createStatement();
            
            // Execute query
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
            
            if (rs.next()) {
                valid = true;
            }
        } catch (Exception e) {
            out.println(e);
        }
        
        if (valid) {
            response.sendRedirect("/home");
        } else {
            response.sendRedirect("/login");
        }
    }
}