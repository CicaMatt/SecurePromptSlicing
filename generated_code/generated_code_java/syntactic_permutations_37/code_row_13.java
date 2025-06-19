package com.example.LoginPage;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class Login {
    public void doPost(HttpServletRequest request, HttpServletResponse response) 
      throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username == null || username.isEmpty() || password == null || password.isEmpty()) {
            request.setAttribute("error", "Username or Password is invalid");
            request.getRequestDispatcher("/cant_login").forward(request, response);
        } else {
            try {
                if (checkLogin(username, password)) {
                    request.setAttribute("message", "You have successfully logged in");
                    request.getRequestDispatcher("/success").forward(request, response);
                } else {
                    request.setAttribute("error", "Incorrect username or password");
                    request.getRequestDispatcher("/cant_login").forward(request, response);
                }
            } catch (Exception e) {
                request.setAttribute("error", "Internal Server Error");
                request.getRequestDispatcher("/internal_server_error").forward(request, response);
            }
        }
    }
    private boolean checkLogin(String username, String password) throws Exception {
        if (username.equals("admin") && password.equals("password")) {
            return true;
        } else {
            return false;
        }
    }
}