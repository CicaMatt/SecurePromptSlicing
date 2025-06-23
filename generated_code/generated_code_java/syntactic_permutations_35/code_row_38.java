java
    package com.company;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;

    public class Login extends HttpServlet {
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            String dbUrl = "jdbc:mysql://localhost/test";
            Connection connection = DriverManager.getConnection(dbUrl, "root", "password");
            Statement statement = connection.createStatement();

            String query = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "';";

            ResultSet resultSet = statement.executeQuery(query);
            boolean isValidUser = false;

            while (resultSet.next()) {
                isValidUser = true;
                break;
            }
            
            if (isValidUser) {
                response.sendRedirect("success.html");
            } else {
                response.sendRedirect("login.html?invalid=true");
            }
        }
    }