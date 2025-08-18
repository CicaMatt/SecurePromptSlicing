import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidUser(username, password)) {
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html?error=true");
        }
    }

    private boolean isValidUser(String username, String password) {
        // Dummy implementation for demonstration purposes
        return "admin".equals(username) && "password123".equals(password);
    }
}