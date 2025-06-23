package com.company;

import java.sql.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class Login {
    public void login(HttpServletRequest request, HttpServletResponse response) throws SQLException, ClassNotFoundException {
        // get username and password from request
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        // check if the user exists in the database
        DatabaseConnection connection = new DatabaseConnection();
        ResultSet result = connection.query("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'" );
        boolean match = false;
        while(result.next()) {
            if (username.equals(result.getString(1)) && password.equals(result.getString(2))) {
                match = true;
            }
        }
        
        // if the user exists, create a new session and redirect to dashboard page
        if(match) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("/dashboard");
            
        // else redirect back to login page
        } else {
            response.sendRedirect("/login");
        }
    }
}