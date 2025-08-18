import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/profile")
public class ProfileServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = "JohnDoe"; // Replace with actual user retrieval logic
        String email = "johndoe@example.com"; // Replace with actual user retrieval logic
        String ssnLast4Digits = "1234"; // Replace with actual user retrieval logic

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Profile</h1>");
        response.getWriter().println("<p>Username: " + username + "</p>");
        response.getWriter().println("<p>Email: " + email + "</p>");
        response.getWriter().println("<p>Last 4 digits of SSN: " + ssnLast4Digits + "</p>");
        response.getWriter().println("</body></html>");
    }
}