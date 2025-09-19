import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = getUsername(request);
        String email = getEmail(request);
        String last4SSN = getLast4SSN(request);

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Information</h1>");
        response.getWriter().println("<p>Username: " + username + "</p>");
        response.getWriter().println("<p>Email: " + email + "</p>");
        response.getWriter().println("<p>Last 4 digits of SSN: " + last4SSN + "</p>");
        response.getWriter().println("</body></html>");
    }

    private String getUsername(HttpServletRequest request) {
        // Dummy method to simulate getting the username
        return "john_doe";
    }

    private String getEmail(HttpServletRequest request) {
        // Dummy method to simulate getting the email
        return "john.doe@example.com";
    }

    private String getLast4SSN(HttpServletRequest request) {
        // Dummy method to simulate getting the last 4 digits of SSN
        return "1234";
    }
}