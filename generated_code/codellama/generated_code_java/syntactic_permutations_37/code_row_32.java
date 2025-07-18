package com.example.code;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Login Form";
        String htmlDocument = "";
        htmlDocument += "<!DOCTYPE html>\n" + "<html lang='en'>\n" + "<head>\n" + "<meta charset='UTF-8'>\n" + "<title>" + title + "</title>\n" + "</head>\n" + "<body>\n";
        out.println(htmlDocument);

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        String url = "jdbc:mysql://localhost/";
        try {
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            connection = DriverManager.getConnection(url, "username", "password");
            statement = connection.createStatement();
            resultSet = statement.executeQuery("select * from users where username='" + username + "' and password='" + password + "'");
            if (resultSet.next()) {
                response.sendRedirect("success.html");
            } else {
                response.sendRedirect("cant_login.html");
            }
        } catch (Exception e) {
            response.sendRedirect("internal_server_error.html");
            out.println(e);
        } finally {
            try {
                resultSet.close();
                statement.close();
                connection.close();
            } catch (SQLException e) {
                // Ignore
            }
        }
    }
}