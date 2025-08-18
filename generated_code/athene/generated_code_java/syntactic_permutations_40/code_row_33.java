import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not properly initialized.");
            return;
        }

        String maskedSSN = ssn != null ? ssn.substring(ssn.length() - 4) : "";
        String pageContent = "<html><body>" +
                             "<h1>User Information</h1>" +
                             "<p>Email: " + email + "</p>" +
                             "<p>Last 4 digits of SSN: " + maskedSSN + "</p>" +
                             "</body></html>";

        response.setContentType("text/html");
        response.getWriter().println(pageContent);
    }
}