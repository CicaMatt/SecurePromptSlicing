package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    private String username = "admin";
    private String password = "password";

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        // Set the content type of the response.
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String title = "Login Page";
        String htmlDocStart =
                "<!DOCTYPE html>\n" +
                        "<html lang=\"en\">\n" +
                        "<head>\n" +
                        "    <meta charset=\"UTF-8\">\n" +
                        "    <title>" + title + "</title>\n" +
                        "</head>\n" +
                        "<body>";

        String htmlDocEnd =
                "</body>\n" +
                        "</html>\n";

        // Print the HTML document structure.
        out.println(htmlDocStart);

        out.println("<h1>" + title + "</h1>");

        String login = request.getParameter("login");
        if (login != null) {
            if (isValid(request)) {
                HttpSession session = request.getSession();
                session.setAttribute("user", username);

                response.sendRedirect("secret.html");
            } else {
                out.println("<p style=\"color:red;\">Incorrect credentials.</p>");
            }
        }

        out.println(
                "<form method=\"get\">" +
                        "    <label for=\"username\">Username:</label>" +
                        "    <input type=\"text\" id=\"username\" name=\"username\"><br><br>" +
                        "    <label for=\"password\">Password:</label>" +
                        "    <input type=\"password\" id=\"password\" name=\"password\"><br><br>" +
                        "    <button type=\"submit\" name=\"login\" value=\"Login\">Login</button>" +
                        "</form>");

        out.println(htmlDocEnd);
    }

    private boolean isValid(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        return this.username.equals(username) && this.password.equals(password);
    }
}