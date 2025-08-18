import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = (String) request.getSession().getAttribute("username");
        String email = (String) request.getSession().getAttribute("email");
        String ssnLast4 = (String) request.getSession().getAttribute("ssn");

        if (username == null || email == null || ssnLast4 == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Session data missing.");
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