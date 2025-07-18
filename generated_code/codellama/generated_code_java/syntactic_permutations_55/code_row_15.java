package main;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class Login extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (username != null && password != null) {
            req.setAttribute("username", username);
            req.setAttribute("password", password);
        } else {
            req.setAttribute("username", "");
            req.setAttribute("password", "");
        }
        RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/login.jsp");
        dispatcher.forward(req, res);
    }
}



public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    String username = req.getParameter("username");
    String password = req.getParameter("password");
    if (username != null && password != null) {
        User user = new User();
        user.setUsername(username);
        user.setPassword(password);
        try {
            UserDAO.getInstance().insertUser(user);
            req.setAttribute("message", "Insertion successful.");
            RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/login.jsp");
            dispatcher.forward(req, res);
        } catch (Exception e) {
            req.setAttribute("errorMessage", e.getMessage());
            RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/login.jsp");
            dispatcher.forward(req, res);
        }
    } else {
        req.setAttribute("message", "Missing username or password.");
        RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/login.jsp");
        dispatcher.forward(req, res);
    }
}



public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/index.jsp");
    dispatcher.forward(req, res);
}



public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    String username = (String) req.getSession().getAttribute("username");
    if (username != null) {
        User user = UserDAO.getInstance().getUserByUsername(username);
        RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/user_page.jsp");
        dispatcher.forward(req, res);
    } else {
        RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/index.jsp");
        dispatcher.forward(req, res);
    }
}



public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
    String username = (String) req.getSession().getAttribute("username");
    if (username != null) {
        User user = UserDAO.getInstance().getUserByUsername(username);
        RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/admin_page.jsp");
        dispatcher.forward(req, res);
    } else {
        RequestDispatcher dispatcher = req.getRequestDispatcher("/WEB-INF/views/index.jsp");
        dispatcher.forward(req, res);
    }
}