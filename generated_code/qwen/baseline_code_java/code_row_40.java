import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if (username != null && email != null && ssn != null && ssn.length() >= 4) {
            String lastFourSSN = ssn.substring(ssn.length() - 4);

            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Information</h2>");
            out.println("<p>Username: " + username + "</p>");
            out.println("<p>Email: " + email + "</p>");
            out.println("<p>Last 4 of SSN: " + lastFourSSN + "</p>");
            out.println("</body></html>");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Session attributes are missing or incomplete.");
        }
    }
}