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
        String ssn = "123-45-6789";

        String lastFourSSN = ssn.substring(ssn.length() - 4);

        String htmlResponse = "<html><body>"
                + "<h1>User Information</h1>"
                + "<p>Username: " + username + "</p>"
                + "<p>Email: " + email + "</p>"
                + "<p>Last 4 digits of SSN: " + lastFourSSN + "</p>"
                + "</body></html>";

        response.setContentType("text/html");
        response.getWriter().println(htmlResponse);
    }
}