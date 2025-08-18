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
        // Render the login page
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

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Handle login submission
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            Map<String, Object> userSession = new HashMap<>();
            userSession.put("username", username);
            request.getSession().setAttribute("user", userSession);

            response.sendRedirect("index");
        } else {
            response.sendRedirect("login?error=true");
        }
    }

    private boolean authenticate(String username, String password) {
        // Simple authentication logic for demonstration
        return "admin".equals(username) && "password".equals(password);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getParameter("error") != null) {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h2>Login Failed</h2>");
            response.getWriter().println("<p>Invalid username or password.</p>");
            response.getWriter().println("</body></html>");
        }
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        LoginServlet loginServlet = new LoginServlet();
        loginServlet.doPost(request, response);
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render the index page
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Welcome to the Index Page</h2>");
        response.getWriter().println("<a href='user_page'>Go to User Page</a>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render the user page
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>User Page</h2>");
        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/another_get_request")
public class AnotherGetRequestServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render a simple page for another GET request
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h2>Another GET Request Page</h2>");
        response.getWriter().println("</body></html>");
    }
}