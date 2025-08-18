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
        String email = (String) request.getSession().getAttribute("email");
        String ssn = (String) request.getSession().getAttribute("ssn");

        if (email == null || ssn == null) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Email and SSN not found in session.");
            return;
        }

        String lastFourSSN = ssn.substring(ssn.length() - 4);

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Email: " + email + "</h2>");
        out.println("<h2>Last 4 digits of SSN: " + lastFourSSN + "</h2>");
        out.println("</body></html>");
    }
}