package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, 
                      HttpServletResponse res) 
        throws ServletException, IOException {
        String username = req.getParameter("username");
        PrintWriter output = res.getWriter();
        output.println("<h1>Hello " + username + "</h1>");
    }
}