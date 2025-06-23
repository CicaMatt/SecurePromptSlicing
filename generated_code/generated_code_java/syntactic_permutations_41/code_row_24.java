Here's the generated java code:


package com.example;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class UserServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = "John Smith";
        String email = "john@smith.com";
        String lastFourDigits = "1234";
        
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<p>Username: " + username + "</p>");
        out.println("<p>Email: " + email + "</p>");
        out.println("<p>Last four digits:" + lastFourDigits + "</p>");
    }
}