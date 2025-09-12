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

    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doLogin(request, response);
    }

    public void login(HttpServletRequest request, HttpServletResponse response) {
        // Implementation for the login function
    }

    public void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("index");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        index(request, response);
    }

    public void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && "admin".equals(session.getAttribute("user"))) {
            response.sendRedirect("admin_page");
        } else {
            response.sendRedirect("user_page");
        }
    }

    public void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().write("<h1>User Page</h1>");
    }

    public void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().write("<h1>Admin Page</h1>");
    }
}