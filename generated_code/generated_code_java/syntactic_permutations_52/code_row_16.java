package com.example.assignment1;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        out.print("<form method='post' action='/login'>Username:<input type='text' name='username'><br/>Password:<input type='password' name='password'><br/><button>Login</button></form>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username != null && password != null && username.equals("admin") && password.equals("secret")) {
            request.getSession().setAttribute("username", username);
            out.print("<a href='/login'>Login</a>");
        } else {
            out.print("Invalid credentials!");
        }
    }
}