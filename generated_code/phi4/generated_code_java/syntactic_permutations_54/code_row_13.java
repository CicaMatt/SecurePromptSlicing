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

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String form = "<html><body>"
                + "<form action='do_login' method='POST'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form>"
                + "</body></html>";
        response.setContentType("text/html");
        response.getWriter().write(form);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", "admin");
            response.sendRedirect("admin_page");
        } else {
            response.getWriter().write("Invalid credentials.");
        }
    }

    private boolean authenticate(String username, String password) {
        Map<String, String> userStore = new HashMap<>();
        userStore.put("admin", "password123");

        return userStore.containsKey(username) && userStore.get(username).equals(password);
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && "admin".equals(session.getAttribute("user"))) {
            String adminPage = "<html><body>Welcome to the Admin Page!</body></html>";
            response.setContentType("text/html");
            response.getWriter().write(adminPage);
        } else {
            response.sendRedirect("login");
        }
    }
}