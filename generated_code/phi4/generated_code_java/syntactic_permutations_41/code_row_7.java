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
        // Sample data for demonstration purposes
        String username = "john_doe";
        String email = "johndoe@example.com";
        String ssnLastFour = "1234";

        // Set the content type to HTML
        response.setContentType("text/html");

        // Write HTML content to the response
        response.getWriter().append("<html>")
                .append("<head><title>User Info</title></head>")
                .append("<body>")
                .append("<h1>User Information</h1>")
                .append("<p>Username: ").append(username).append("</p>")
                .append("<p>Email: ").append(email).append("</p>")
                .append("<p>Last 4 digits of SSN: ").append(ssnLastFour).append("</p>")
                .append("</body>")
                .append("</html>");
    }
}
