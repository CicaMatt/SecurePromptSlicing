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


To run this code:

1. You need to set up a web server that supports Servlets, such as Apache Tomcat or Jetty.
2. Place the `InfoServlet` class in your web application's directory structure, typically under `src/main/java`.
3. Configure your `web.xml` file to map the servlet URL pattern `/info` to this class, if not using annotations.
4. Deploy and run your web application on the server.