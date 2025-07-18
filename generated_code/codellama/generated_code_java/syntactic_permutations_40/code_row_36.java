package com.example.demo;

import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
        String username = (String)req.getSession().getAttribute("username");
        String email = (String)req.getSession().getAttribute("email");
        String ssn = (String)req.getSession().getAttribute("ssn");

        res.setContentType("text/html");
        PrintWriter out = res.getWriter();
        out.println("<h1>Welcome " + username + "</h1>");
        out.println("<p>Your email is: " + email + "</p>");
        out.println("<p>Your SSN is: " + ssn + "</p>");
    }
}