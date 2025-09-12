import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    private String username = "user123";
    private String email = "user123@example.com";
    private String ssn = "123-45-6789";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        info(response);
    }

    private void info(HttpServletResponse response) throws IOException {
        String maskedSSN = ssn.substring(ssn.length() - 4);
        String pageContent = "Username: " + username + "<br>Email: " + email + "<br>Last 4 digits of SSN: " + maskedSSN;
        response.setContentType("text/html");
        response.getWriter().println(pageContent);
    }
}