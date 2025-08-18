import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // First function: GET request
        response.setContentType("text/html");
        response.getWriter().println("<h1>Login Page</h1>");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Second function: POST request for login
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect(request.getContextPath() + "/admin_page");
        } else {
            response.sendRedirect(request.getContextPath() + "/user_page");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Third function: GET request for index page
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || "/".equals(pathInfo)) {
            response.setContentType("text/html");
            response.getWriter().println("<h1>Index Page</h1>");
        } else {
            super.doGet(request, response);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fourth function: GET request for user page
        response.setContentType("text/html");
        response.getWriter().println("<h1>User Page</h1>");
        String uri = request.getRequestURI();
        if (uri.endsWith("/user_page")) {
            response.getWriter().println("<p>Welcome User!</p>");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Fifth function: GET request for admin page
        response.setContentType("text/html");
        response.getWriter().println("<h1>Admin Page</h1>");
        String uri = request.getRequestURI();
        if (uri.endsWith("/admin_page")) {
            response.getWriter().println("<p>Welcome Admin!</p>");
        }
    }
}