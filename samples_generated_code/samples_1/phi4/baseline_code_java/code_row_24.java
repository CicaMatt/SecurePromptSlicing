import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // Mock user data
        String username = "JohnDoe";
        String email = "johndoe@example.com";
        String ssnLast4 = "1234";

        response.setContentType("text/html");
        response.getWriter().append("<html><body>")
                .append("<h1>User Information</h1>")
                .append("<p>Username: ").append(username).append("</p>")
                .append("<p>Email: ").append(email).append("</p>")
                .append("<p>Last 4 digits of SSN: ****").append(ssnLast4).append("</p>")
                .append("</body></html>");
    }
}
