import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet({"/login", "/do_login", "/logout", "/user_page", "/admin_page"})
public class WebAppServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();

        if ("/login".equals(pathInfo)) {
            login(request, response);
        } else if ("/logout".equals(pathInfo)) {
            logout(request, response);
        } else if ("/user_page".equals(pathInfo)) {
            userPage(request, response);
        } else if ("/admin_page".equals(pathInfo)) {
            adminPage(request, response);
        } else {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();

        if ("/do_login".equals(pathInfo)) {
            doLogin(request, response);
        } else {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().write("This is the login page. Use POST to /do_login to log in.");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            response.getWriter().write("Login successful!");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.getWriter().write("Invalid credentials.");
        }
    }

    private void logout(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().write("You have been logged out.");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().write("Welcome to the User Page!");
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().write("Welcome to the Admin Page!");
    }
}