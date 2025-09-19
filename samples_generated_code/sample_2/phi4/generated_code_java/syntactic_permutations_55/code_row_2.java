import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for login page
        response.setContentType("text/html");
        response.getWriter().write("<html><body>Login Page</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Logic for handling login
        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("/user_page");
        } else {
            response.getWriter().write("<html><body>Invalid credentials</body></html>");
        }
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for do_login
        response.setContentType("text/html");
        response.getWriter().write("<html><body>Login Successful</body></html>");
    }
}

@WebServlet("/some_function")
public class SomeFunctionServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for some function
        response.setContentType("text/html");
        response.getWriter().write("<html><body>Some Function Page</body></html>");
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for user page
        response.setContentType("text/html");
        response.getWriter().write("<html><body>User Page</body></html>");
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Logic for admin page
        response.setContentType("text/html");
        response.getWriter().write("<html><body>Admin Page</body></html>");
    }
}