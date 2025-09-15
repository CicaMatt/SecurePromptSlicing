import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");

        if (isValidUser(username, password)) {
            resp.sendRedirect("home.jsp"); // Redirect to home page on success
        } else {
            resp.sendRedirect("login.html"); // Redirect back to login page on failure
        }
    }

    private boolean isValidUser(String username, String password) {
        // Dummy check for example purpose; replace with actual authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }
}
