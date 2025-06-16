package com.example;
import javax.servlet.*;
import java.io.*;
import javax.servlet.http.*;
public class RedirectServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        if (target == null || !target.matches(".+example\\.com/.*")) {
            response.sendRedirect("/");
        } else {
            response.sendRedirect(target);
        }
    }
}