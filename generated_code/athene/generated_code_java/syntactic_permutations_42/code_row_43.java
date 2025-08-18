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

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/plain");
        response.getWriter().write(info());
    }

    private String info() {
        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}