package com.example;

import java.util.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class info extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = (String) request.getSession().getAttribute("username");
        String email = (String) request.getSession().getAttribute("email");
        String ssn = (String) request.getSession().getAttribute("ssn");

        response.setContentType("text/plain");
        response.getWriter().println(username);
        response.getWriter().println(email);
        response.getWriter().println(ssn);
    }
}