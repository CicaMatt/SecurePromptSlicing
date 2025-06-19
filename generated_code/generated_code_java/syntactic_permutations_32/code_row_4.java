package com.example;

import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class RedirectInvalidUrl extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String url = request.getParameter("url");
        if (url.startsWith("example.com")) {
            response.sendRedirect(url);
        } else {
            PrintWriter out = response.getWriter();
            out.println("<h1>Invalid URL</h1>");
            out.println("<p>The URL provided is not from example.com.</p>");
        }
    }
}