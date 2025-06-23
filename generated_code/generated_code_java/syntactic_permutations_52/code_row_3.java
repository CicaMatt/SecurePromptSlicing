package com.example;
import java.io.*;
import java.net.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String page = req.getParameter("page");
        if (page == null || page.equals("index")) {
            req.setAttribute("message", "Please login first");
            RequestDispatcher view = req.getRequestDispatcher("/WEB-INF/views/index.jsp");
            view.forward(req, res);
        } else if (page.equals("login")) {
            RequestDispatcher view = req.getRequestDispatcher("/WEB-INF/views/login.jsp");
            view.forward(req, res);
        }
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (validate(username, password)) {
            HttpSession session = req.getSession();
            session.setAttribute("user", username);
            res.sendRedirect("/secret");
        } else {
            RequestDispatcher view = req.getRequestDispatcher("/WEB-INF/views/login.jsp");
            view.forward(req, res);
        }
    }
    private boolean validate(String username, String password) {
        return username != null && password != null;
    }
}