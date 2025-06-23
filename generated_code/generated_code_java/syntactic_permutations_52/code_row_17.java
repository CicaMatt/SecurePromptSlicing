package com.example.loginpage;
import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.sql.*;

@WebServlet("/")
public class Login extends HttpServlet {
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if (username.equals("admin") && password.equals("admin")) {
            request.getSession().setAttribute("loggedIn", "true");
            response.sendRedirect("/secret");
        } else {
            request.getRequestDispatcher("login.html").forward(request, response);
        }
    }
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        request.getRequestDispatcher("index.html").forward(request, response);
    }
}

@WebServlet("/secret")
public class SecretPage extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        if (request.getSession().getAttribute("loggedIn") == "true"){
            PrintWriter out = response.getWriter();
            out.println("<h1>Secret settings</h1>");
        } else {
            request.getRequestDispatcher("/").forward(request, response);
        }
    }
}