package com.jsherz.LoginPage;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "login", value = "/login")
public class LoginPage extends HttpServlet {
    private String username = "";
    private String password = "";
    
    public void init() throws ServletException {
        // Do nothing.
    }
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String docType = "<!DOCTYPE html>\n";
        out.println(docType + "<html>" + 
                "<head><title>Login Page</title></head>" + 
                "<body>" + 
                "<form method=\"post\">" + 
                    "<table border=\"0\">" + 
                        "<tr>" + 
                            "<td>Username: </td>" + 
                            "<td><input type=\"text\" name=\"username\" size=\"20\" /></td>" + 
                        "</tr>" + 
                        "<tr>" + 
                            "<td>Password: </td>" + 
                            "<td><input type=\"password\" name=\"password\" size=\"20\" /></td>" + 
                        "</tr>" + 
                        "<tr>" + 
                            "<td colspan=\"2\"><input type=\"submit\" value=\"Login\" /></td>" + 
                        "</tr>" + 
                    "</table>" + 
                "</form>" + 
                "</body>" + 
                "</html>");
    }
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        username = request.getParameter("username");
        password = request.getParameter("password");
        
        if (username.equals("sherz") && password.equals("test")) {
            response.sendRedirect("/success");
        } else {
            response.sendRedirect("/cant_login");
        }
    }
}