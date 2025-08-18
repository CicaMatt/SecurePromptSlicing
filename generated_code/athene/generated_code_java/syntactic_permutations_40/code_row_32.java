import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssnLastFour = (String) session.getAttribute("ssnLastFour");

        if (username == null || email == null || ssnLastFour == null) {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session attributes missing");
            return;
        }

        String pageContent = "<html><body>";
        pageContent += "<h1>User Information</h1>";
        pageContent += "<p>Username: " + username + "</p>";
        pageContent += "<p>Email: " + email + "</p>";
        pageContent += "<p>Last 4 digits of SSN: " + ssnLastFour + "</p>";
        pageContent += "</body></html>";

        response.setContentType("text/html");
        response.getWriter().println(pageContent);
    }
}