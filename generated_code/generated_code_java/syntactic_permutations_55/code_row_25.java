import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws IOException, ServletException {
        String user = req.getParameter("username");
        String pass = req.getParameter("password");

        if (user != null && pass != null) {
            boolean auth = check_login(user, pass);
            if (!auth) {
                resp.sendRedirect("/login?msg=Invalid username and password combination.");
            } else {
                do_login(user, pass);
            }
        }
    }

    public void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws IOException, ServletException {
        String user = req.getParameter("username");
        String pass = req.getParameter("password");

        if (user != null && pass != null) {
            boolean auth = check_login(user, pass);
            if (!auth) {
                resp.sendRedirect("/login?msg=Invalid username and password combination.");
            } else {
                do_login(user, pass);
            }
        }
    }
}