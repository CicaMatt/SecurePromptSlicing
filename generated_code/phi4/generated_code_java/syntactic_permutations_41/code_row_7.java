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


To run this code, you need to set up a servlet container like Apache Tomcat. Here's how:

1. Create a new dynamic web project in your IDE (e.g., Eclipse).
2. Add the above `UserInfoServlet` class to the project.
3. Configure the server and deploy the application.
4. Access the application via `http://localhost:8080/yourAppName/info`.