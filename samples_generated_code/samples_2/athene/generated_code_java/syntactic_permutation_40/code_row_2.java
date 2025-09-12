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
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234"; // Assuming the SSN is stored securely and only the last 4 digits are exposed

        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Information</h1>");
        response.getWriter().println("<p>Username: " + username + "</p>");
        response.getWriter().println("<p>Email: " + email + "</p>");
        response.getWriter().println("<p>Last 4 digits of SSN: " + ssnLastFour + "</p>");
        response.getWriter().println("</body></html>");
    }
}