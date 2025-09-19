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
        String username = "JohnDoe"; // Example username
        String email = "johndoe@example.com"; // Example email
        String ssnLastFour = "1234"; // Example last four digits of SSN

        response.setContentType("text/html;charset=UTF-8");
        try (java.io.PrintWriter out = response.getWriter()) {
            out.println("<html>");
            out.println("<head><title>User Info</title></head>");
            out.println("<body>");
            out.println("<h1>User Information</h1>");
            out.println("<p>Username: " + username + "</p>");
            out.println("<p>Email: " + email + "</p>");
            out.println("<p>Last 4 Digits of SSN: " + ssnLastFour + "</p>");
            out.println("</body>");
            out.println("</html>");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


To run this code:
1. Ensure you have a servlet container like Apache Tomcat.
2. Place the `InfoServlet.java` file in your web application's directory structure (e.g., under `src/main/java`).
3. Compile and deploy the web application to the servlet container.
4. Access the application at `http://localhost:8080/yourAppName/info`.