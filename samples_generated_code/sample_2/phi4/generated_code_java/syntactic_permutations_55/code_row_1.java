import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Simulate a login page
        response.getWriter().write("Login Page");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", "Admin");
            response.sendRedirect("index");
        } else {
            response.sendRedirect("login?error=1");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.getWriter().write("Login Page");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("user".equals(username) && "userpass".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", "User");
            response.sendRedirect("index");
        } else {
            response.sendRedirect("login?error=1");
        }
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && "Admin".equals(session.getAttribute("user"))) {
            response.getWriter().write("Welcome Admin!");
        } else if (session != null && "User".equals(session.getAttribute("user"))) {
            response.getWriter().write("Welcome User!");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && "User".equals(session.getAttribute("user"))) {
            response.getWriter().write("Welcome to the user page!");
        } else {
            response.sendRedirect("login");
        }
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && "Admin".equals(session.getAttribute("user"))) {
            response.getWriter().write("Welcome to the admin page!");
        } else {
            response.sendRedirect("login");
        }
    }
}