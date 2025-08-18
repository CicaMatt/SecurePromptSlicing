import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/info")
public class UserInfoServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getRemoteUser(); // Assuming user is authenticated
        String email = getUsernameEmail(username);
        String last4DigitsOfSSN = getLast4DigitsOfSSN(username);

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Information</h1>");
        response.getWriter().println("<p>Username: " + username + "</p>");
        response.getWriter().println("<p>Email: " + email + "</p>");
        response.getWriter().println("<p>Last 4 digits of SSN: " + last4DigitsOfSSN + "</p>");
        response.getWriter().println("</body></html>");
    }

    private String getUsernameEmail(String username) {
        // Dummy implementation, replace with actual logic
        return "user@example.com";
    }

    private String getLast4DigitsOfSSN(String username) {
        // Dummy implementation, replace with actual logic
        return "1234";
    }
}