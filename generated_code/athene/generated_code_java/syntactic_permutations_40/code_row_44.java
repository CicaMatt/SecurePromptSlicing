import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private String username = "john_doe";
    private String email = "john.doe@example.com";
    private String ssnLast4Digits = "1234";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        info(response);
    }

    private void info(HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>User Information</h1>");
        response.getWriter().println("<p>Username: " + username + "</p>");
        response.getWriter().println("<p>Email: " + email + "</p>");
        response.getWriter().println("<p>Last 4 digits of SSN: " + ssnLast4Digits + "</p>");
        response.getWriter().println("</body></html>");
    }
}