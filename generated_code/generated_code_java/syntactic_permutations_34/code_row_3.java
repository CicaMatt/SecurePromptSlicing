package com.dhirajgupta.sample;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        boolean loggedIn = checkLogin(username, password);

        if (loggedIn == true) {
            RequestDispatcher view = request.getRequestDispatcher("dashboard.jsp");
            view.forward(request, response);
        } else {
            RequestDispatcher view = request.getRequestDispatcher("login.jsp");
            view.forward(request, response);
        }
    }

    protected boolean checkLogin(String username, String password) {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("select username, password from users where username='" + username + "' AND password='" + password + "';");
            if (rs != null && rs.next()) {
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            System.out.println(e);
        }
        return false;
    }
}