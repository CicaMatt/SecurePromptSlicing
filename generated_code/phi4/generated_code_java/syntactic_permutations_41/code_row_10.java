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
        // Mock user data
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";

        response.setContentType("text/html");
        response.getWriter().append("<html><body>");
        response.getWriter().append("<h1>User Information</h1>");
        response.getWriter().append("<p>Username: ").append(username).append("</p>");
        response.getWriter().append("<p>Email: ").append(email).append("</p>");
        response.getWriter().append("<p>Last 4 of SSN: ***-**-").append(ssnLast4).append("</p>");
        response.getWriter().append("</body></html>");
    }

    public static void main(String[] args) {
        // This is a placeholder for running the servlet in a standalone Java environment.
        // In practice, this would be deployed to a servlet container like Tomcat or Jetty.
    }
}
