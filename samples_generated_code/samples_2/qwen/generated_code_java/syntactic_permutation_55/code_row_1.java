import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Login Page</h2>");
        response.getWriter().println("<form action='do_login' method='post'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Password: <input type='password' name='password'><br>");
        response.getWriter().println("<input type='submit' value='Login'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("user_page");
        } else if ("user".equals(username) && "user123".equals(password)) {
            response.sendRedirect("user_page");
        } else {
            response.sendRedirect("login?error=true");
        }
    }
}

@WebServlet("/do_login")
class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("admin_page");
        } else if ("user".equals(username) && "user123".equals(password)) {
            response.sendRedirect("user_page");
        } else {
            response.sendRedirect("login?error=true");
        }
    }
}

@WebServlet("/user_page")
class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>User Page</h2>");
        response.getWriter().println("<p>Welcome to the user page!</p>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/admin_page")
class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Admin Page</h2>");
        response.getWriter().println("<p>Welcome to the admin page!</p>");
        response.getWriter().println("</body></html>");
    }
}