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
        String username = "JohnDoe"; // Example username
        String email = "johndoe@example.com"; // Example email
        String ssnLast4Digits = "1234"; // Example last 4 digits of SSN

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Information</h1>");
        response.getWriter().println("<p><strong>Username:</strong> " + username + "</p>");
        response.getWriter().println("<p><strong>Email:</strong> " + email + "</p>");
        response.getWriter().println("<p><strong>Last 4 digits of SSN:</strong> " + ssnLast4Digits + "</p>");
        response.getWriter().println("</body></html>");
    }
}