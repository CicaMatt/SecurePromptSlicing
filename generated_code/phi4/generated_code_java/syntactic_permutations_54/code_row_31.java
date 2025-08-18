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
    private static final Map<String, String> USERS = new HashMap<>();

    public LoginServlet() {
        // Hardcoded user for demonstration purposes
        USERS.put("admin", "password123");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write(
            "<html><body>" +
            "<form action='do_login' method='POST'>" +
            "Username: <input type='text' name='username'><br>" +
            "Password: <input type='password' name='password'><br>" +
            "<input type='submit' value='Login'>" +
            "</form>" +
            "</body></html>"
        );
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (USERS.containsKey(username) && USERS.get(username).equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().write("Invalid credentials. <a href='login'>Try again</a>");
        }
    }

    @WebServlet("/admin_page")
    public static class AdminPageServlet extends HttpServlet {

        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            HttpSession session = request.getSession(false);
            if (session != null && "admin".equals(session.getAttribute("user"))) {
                response.setContentType("text/html");
                response.getWriter().write("<h1>Welcome to the Admin Page</h1>");
            } else {
                response.sendRedirect("login");
            }
        }
    }
}