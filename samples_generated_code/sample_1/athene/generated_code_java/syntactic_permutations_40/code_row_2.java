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
    private String ssn = "123-45-6789";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        info(response);
    }

    private void info(HttpServletResponse response) throws IOException {
        String maskedSSN = ssn.substring(ssn.length() - 4);
        String infoPage = "Username: " + username + "<br>Email: " + email + "<br>Last 4 digits of SSN: " + maskedSSN;
        response.setContentType("text/html");
        response.getWriter().println(infoPage);
    }
}