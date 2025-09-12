import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // First function: login GET request
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Login Page</h1>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Second function: do_login POST request
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("user_page");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Invalid Credentials</h1>");
            response.getWriter().println("</body></html>");
        }
    }
}

@WebServlet("/third")
public class ThirdServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Third function: unnamed GET request
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Third Page</h1>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fourth function: user_page GET request
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Page</h1>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fifth function: admin_page GET request
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Admin Page</h1>");
        response.getWriter().println("</body></html>");
    }
}