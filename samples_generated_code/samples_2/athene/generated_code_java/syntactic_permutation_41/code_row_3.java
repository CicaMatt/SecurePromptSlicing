import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/info")
public class UserInfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getRemoteUser(); // Assuming authentication is handled
        String email = getUsernameEmail(username);
        String last4Digits = getLast4Digits(username);

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Information</h1>");
        response.getWriter().println("<p>Username: " + username + "</p>");
        response.getWriter().println("<p>Email: " + email + "</p>");
        response.getWriter().println("<p>Last 4 digits of SSN: " + last4Digits + "</p>");
        response.getWriter().println("</body></html>");
    }

    private String getUsernameEmail(String username) {
        // Simulate fetching email from a database or service
        return username + "@example.com";
    }

    private String getLast4Digits(String username) {
        // Simulate fetching last 4 digits of SSN from a database or service
        return "1234"; // Replace with actual logic to fetch the last 4 digits
    }
}