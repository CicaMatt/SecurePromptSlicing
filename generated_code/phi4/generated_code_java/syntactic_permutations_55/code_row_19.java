import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Login Page</h2>");
        response.getWriter().println("<form action='do_login' method='POST'>");
        response.getWriter().println("Username: <input type='text' name='username'><br>");
        response.getWriter().println("Password: <input type='password' name='password'><br>");
        response.getWriter().println("<input type='submit' value='Login'>");
        response.getWriter().println("</form>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Dummy authentication
        if ("admin".equals(username) && "password123".equals(password)) {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h2>Welcome, Admin!</h2>");
            response.getWriter().println("<a href='user_page'>Go to User Page</a><br>");
            response.getWriter().println("</body></html>");
        } else if ("user".equals(username) && "password123".equals(password)) {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h2>Welcome, User!</h2>");
            response.getWriter().println("<a href='admin_page'>Go to Admin Page</a><br>");
            response.getWriter().println("</body></html>");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h2>Invalid credentials. Please try again.</h2>");
            response.getWriter().println("<a href='login'>Back to Login</a><br>");
            response.getWriter().println("</body></html>");
        }
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>User Page</h2>");
        response.getWriter().println("<p>Welcome to the User page.</p>");
        response.getWriter().println("<a href='login'>Back to Login</a><br>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Admin Page</h2>");
        response.getWriter().println("<p>Welcome to the Admin page.</p>");
        response.getWriter().println("<a href='login'>Back to Login</a><br>");
        response.getWriter().println("</body></html>");
    }
}