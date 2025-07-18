package com.app;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class LoginServlet extends HttpServlet {

    private static final Log logger = LogFactory.getLog(LoginServlet.class);

    @Override
    public void init() throws ServletException {
        super.init();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        String user = (String) req.getSession().getAttribute("user");

        if (user == null || user.isEmpty()) {
            logger.info("User is not logged in.");
            RequestDispatcher rd = req.getRequestDispatcher("/login.jsp");
            rd.forward(req, resp);
        } else {
            String role = (String) req.getSession().getAttribute("role");
            if ("admin".equalsIgnoreCase(role)) {
                logger.info("User is an admin.");
                RequestDispatcher rd = req.getRequestDispatcher("/admin.jsp");
                rd.forward(req, resp);
            } else {
                logger.info("User is a regular user.");
                RequestDispatcher rd = req.getRequestDispatcher("/user.jsp");
                rd.forward(req, resp);
            }
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        String username = req.getParameter("username");
        String password = req.getParameter("password");

        if (username == null || username.isEmpty() || password == null || password.isEmpty()) {
            RequestDispatcher rd = req.getRequestDispatcher("/login.jsp");
            rd.forward(req, resp);
        } else {
            UserDAO userDao = new UserDAO();
            User user = userDao.authenticateUser(username, password);

            if (user != null) {
                req.getSession().setAttribute("user", user);
                req.getSession().setAttribute("role", user.getRole());
                String role = (String) req.getSession().getAttribute("role");
                if ("admin".equalsIgnoreCase(role)) {
                    RequestDispatcher rd = req.getRequestDispatcher("/admin.jsp");
                    rd.forward(req, resp);
                } else {
                    RequestDispatcher rd = req.getRequestDispatcher("/user.jsp");
                    rd.forward(req, resp);
                }
            } else {
                String message = "Invalid credentials";
                req.setAttribute("message", message);
                RequestDispatcher rd = req.getRequestDispatcher("/login.jsp");
                rd.forward(req, resp);
            }
        }
    }
}