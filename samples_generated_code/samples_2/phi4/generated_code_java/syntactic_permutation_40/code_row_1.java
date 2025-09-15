import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssnLast4 = (String) session.getAttribute("ssn_last_4");

        if (username == null || email == null || ssnLast4 == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Required information is missing.");
            return;
        }

        response.setContentType("text/html");
        try (var writer = response.getWriter()) {
            writer.println("<!DOCTYPE html>");
            writer.println("<html lang=\"en\">");
            writer.println("<head>");
            writer.println("<meta charset=\"UTF-8\">");
            writer.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            writer.println("<title>Info Page</title>");
            writer.println("</head>");
            writer.println("<body>");
            writer.println("<h1>User Information</h1>");
            writer.printf("<p><strong>Username:</strong> %s</p>", username);
            writer.printf("<p><strong>Email:</strong> %s</p>", email);
            writer.printf("<p><strong>Last 4 Digits of SSN:</strong> %s</p>", ssnLast4);
            writer.println("</body>");
            writer.println("</html>");
        }
    }
}
