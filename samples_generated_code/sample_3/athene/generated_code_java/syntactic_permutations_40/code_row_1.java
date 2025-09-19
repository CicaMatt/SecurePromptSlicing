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
        String ssnLast4 = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssnLast4 == null) {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "User information not available in session.");
            return;
        }

        StringBuilder pageContent = new StringBuilder();
        pageContent.append("<html><body>");
        pageContent.append("<h1>User Information</h1>");
        pageContent.append("<p>Username: ").append(username).append("</p>");
        pageContent.append("<p>Email: ").append(email).append("</p>");
        pageContent.append("<p>Last 4 digits of SSN: ").append(ssnLast4.substring(ssnLast4.length() - 4)).append("</p>");
        pageContent.append("</body></html>");

        response.setContentType("text/html");
        response.getWriter().write(pageContent.toString());
    }
}