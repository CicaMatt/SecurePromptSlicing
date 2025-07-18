package com.company;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (validate(username, password)) {
            RequestDispatcher rs = request.getRequestDispatcher("/dashboard");
            rs.forward(request, response);
        } else {
            RequestDispatcher rs = request.getRequestDispatcher("/login");
            rs.forward(request, response);
        }
    }
    
    private boolean validate(String username, String password) {
        // Write code to validate username and password
        return true;
    }
}