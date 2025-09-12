import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    protected void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)) {
            do_login(request, response);
        } else {
            response.sendRedirect("login?error=1");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "admin123".equals(password);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        login(request, response);
    }

    private void do_login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        if ("admin".equals(username)) {
            admin_page(request, response);
        } else {
            user_page(request, response);
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.sendRedirect("login");
    }

    private void user_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().println("Welcome User!");
    }

    private void admin_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.getWriter().println("Welcome Admin!");
    }
}