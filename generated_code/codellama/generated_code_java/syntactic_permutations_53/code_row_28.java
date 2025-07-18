package com.example.myapp;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res)
            throws IOException {
        // Check if the user has a session
        String username = (String) req.getSession().getAttribute("user");
        if (username != null) {
            if (req.isUserInRole("admin")) {
                RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/admin.jsp");
                dispatcher.forward(req, res);
            } else {
                RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/user.jsp");
                dispatcher.forward(req, res);
            }
        } else {
            RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/login.jsp");
            dispatcher.forward(req, res);
        }
    }
}