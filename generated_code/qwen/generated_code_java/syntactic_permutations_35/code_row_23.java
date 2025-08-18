import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        boolean isValidUser = false;

        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "root", "password")) {
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();
            isValidUser = resultSet.next();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        if (isValidUser) {
            response.sendRedirect("home.jsp");
        } else {
            response.sendRedirect("login.html");
        }
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServletConfig extends HttpServlet {
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException(e);
        }
    }
}



<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <form action="LoginServlet" method="post">
        Username: <input type="text" name="username"><br/>
        Password: <input type="password" name="password"><br/>
        <input type="submit" value="Login">
    </form>
</body>
</html>



<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Home Page</title>
</head>
<body>
    <h2>Welcome to the Home Page!</h2>
</body>
</html>