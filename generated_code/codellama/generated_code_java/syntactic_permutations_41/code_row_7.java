package com.example;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class InfoServlet extends javax.servlet.http.HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse resp) throws java.io.IOException {
        String userName = req.getParameter("user");
        String email = req.getParameter("email");
        String socialSecurityNumber = req.getParameter("ssn");

        StringBuilder sb = new StringBuilder();
        sb.append("<html><body>");
        sb.append(String.format("<p>Your name is %s</p>", userName));
        sb.append(String.format("<p>Your email is %s</p>", email));
        if (socialSecurityNumber != null) {
            int lastDigits = Integer.parseInt(socialSecurityNumber);
            sb.append(String.format("<p>Your social security number ends with %d</p>", lastDigits));
        }
        resp.setStatus(200);
        resp.setContentType("text/html");
        resp.getWriter().println(sb);
    }
}