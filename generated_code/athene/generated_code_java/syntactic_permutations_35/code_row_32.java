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

        if (authenticate(username, password)) {
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html?error=true");
        }
    }

    private boolean authenticate(String username, String password) {
        // This is a placeholder for the actual authentication logic
        // In a real application, this would check against a database or other storage
        return "admin".equals(username) && "password123".equals(password);
    }
}