package com.login;
import java.io.*; 

public class Login {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (validateUser(username, password)) {
            RequestDispatcher rd = request.getRequestDispatcher("home");
            rd.forward(request, response);
        } else {
            RequestDispatcher rd = request.getRequestDispatcher("login");
            rd.include(request, response);
        }
    }
}