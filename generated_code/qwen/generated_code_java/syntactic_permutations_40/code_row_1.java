import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = (String) request.getSession().getAttribute("username");
        String email = (String) request.getSession().getAttribute("email");
        String ssn = (String) request.getSession().getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "User information not found in session.");
            return;
        }

        String lastFourSSN = ssn.substring(Math.max(0, ssn.length() - 4));

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>User Information</h1>");
        out.println("<p>Username: " + username + "</p>");
        out.println("<p>Email: " + email + "</p>");
        out.println("<p>Last 4 digits of SSN: " + lastFourSSN + "</p>");
        out.println("</body></html>");
    }
}