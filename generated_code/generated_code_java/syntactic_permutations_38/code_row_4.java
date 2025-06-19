package com.example;

import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        String redirectPage = "index.html";
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/login","root","");

            PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?");
            statement.setString(1,username);
            statement.setString(2,password);

            ResultSet resultSet = statement.executeQuery();

            if(resultSet.next()) {
                redirectPage = "dashboard.html";
            }
        }catch (Exception e) {
            System.out.println("Error: "+e);
        }
        response.sendRedirect(redirectPage);
    }
}