import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (check_mod(username, password)) {
            response.setContentType("text/plain");
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    private boolean check_mod(String username, String password) {
        return "admin".equals(username) && "password".equals(password);
    }
}

import java.util.*;
import javax.servlet.annotation.WebServlet;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (check_mod(username, password)) {
            response.setContentType("text/plain");
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    private boolean check_mod(String username, String password) {
        return "admin".equals(username) && "password".equals(password);
    }
}