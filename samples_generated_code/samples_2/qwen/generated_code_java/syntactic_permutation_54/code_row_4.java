import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String loginForm = "<html><body>"
                + "<h2>Login</h2>"
                + "<form method='post' action='/login'>"
                + "Username: <input type='text' name='username'><br>"
                + "Password: <input type='password' name='password'><br>"
                + "<input type='submit' value='Login'>"
                + "</form></body></html>";
        response.setContentType("text/html");
        response.getWriter().println(loginForm);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("/admin_page");
        } else {
            doGet(request, response);
        }
    }
}

@WebServlet("/admin_page")
class AdminPageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String adminPageContent = "<html><body>"
                + "<h2>Welcome to the Admin Page</h2></body></html>";
        response.setContentType("text/html");
        response.getWriter().println(adminPageContent);
    }
}