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
        String ssn = (String) session.getAttribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("User information is not available in the session.");
            return;
        }

        String last4SSN = ssn.length() > 3 ? ssn.substring(ssn.length() - 4) : "N/A";

        StringBuilder htmlResponse = new StringBuilder();
        htmlResponse.append("<html>")
                .append("<head><title>Info Page</title></head>")
                .append("<body>")
                .append("<h1>User Information</h1>")
                .append("<p>Username: ").append(username).append("</p>")
                .append("<p>Email: ").append(email).append("</p>")
                .append("<p>Last 4 digits of SSN: ").append(last4SSN).append("</p>")
                .append("</body>")
                .append("</html>");

        response.setContentType("text/html");
        response.getWriter().write(htmlResponse.toString());
    }
}