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

    private static final Map<String, String> users = new HashMap<>();

    static {
        // Dummy data for demonstration purposes
        users.put("user1", "password123");
        users.put("admin", "adminpass");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isValidLogin(username, password)) {
            response.sendRedirect("/home.jsp"); // Redirect to home page on successful login
        } else {
            response.getWriter().println("Invalid username or password.");
        }
    }

    private boolean isValidLogin(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            return true;
        }
        return false;
    }
}
