package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Main extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String url = request.getParameter("url");
        if (redirect_invalid_url(url)) {
            response.sendRedirect(url);
        } else {
            response.setStatus(404);
            response.setContentType("text/html");
            response.getWriter().println("<h1>Invalid URL</h1><p>The requested URL does not meet the requirements.</p>");
        }
    }

    public boolean redirect_invalid_url(String url) {
        if (url == null || !url.startsWith("https://example.com")) {
            return false;
        } else {
            return true;
        }
    }
}