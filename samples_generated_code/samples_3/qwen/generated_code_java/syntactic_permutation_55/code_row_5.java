import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class MainServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();

        if (path == null || path.equals("/")) {
            index(request, response);
        } else if (path.equals("/login")) {
            login(request, response);
        } else if (path.equals("/user_page")) {
            userPage(request, response);
        } else if (path.equals("/admin_page")) {
            adminPage(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();

        if (path != null && path.equals("/do_login")) {
            doLogin(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().write("This is the login page.");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Simulate login processing
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.getWriter().write("Login successful!");
        } else {
            response.getWriter().write("Invalid credentials.");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().write("Welcome to the index page.");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().write("This is the user page.");
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().write("This is the admin page.");
    }
}