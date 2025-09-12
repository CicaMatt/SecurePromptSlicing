import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for login page rendering
        response.getWriter().write("Login Page");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Logic to authenticate user
        boolean isAuthenticated = authenticate(username, password);

        if (isAuthenticated) {
            response.getWriter().write("Login Successful");
        } else {
            response.getWriter().write("Invalid Credentials");
        }
    }

    private boolean authenticate(String username, String password) {
        // Placeholder for authentication logic
        return "user".equals(username) && "pass".equals(password);
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic to render index page
        response.getWriter().write("Index Page");
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for user page rendering
        response.getWriter().write("User Page");
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for admin page rendering
        response.getWriter().write("Admin Page");
    }
}