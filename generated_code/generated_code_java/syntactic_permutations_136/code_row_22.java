package com.example;

import javax.servlet.*;
import java.io.*;
import java.net.*;

public class Servlet extends GenericServlet {
    public void service(ServletRequest request, ServletResponse response) throws IOException, ServletException {
        if (request.getMethod().equals("GET")) {
            PrintWriter out = response.getWriter();
            out.println("<html>");
            out.println("<body>");
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            if (check_mod(username, password)) {
                out.println("true");
            }
            out.println("</body>");
            out.println("</html>");
        }
    }

    public boolean check_mod(String username, String password) {
        return true;
    }
}