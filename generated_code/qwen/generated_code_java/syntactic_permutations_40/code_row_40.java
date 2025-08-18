import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssnLastFour = (String) session.getAttribute("ssnLastFour");

            if (username != null && email != null && ssnLastFour != null) {
                response.setContentType("text/html");
                response.getWriter().println("<html><body>");
                response.getWriter().println("<h1>User Information</h1>");
                response.getWriter().println("<p>Username: " + username + "</p>");
                response.getWriter().println("<p>Email: " + email + "</p>");
                response.getWriter().println("<p>Last 4 of SSN: " + ssnLastFour + "</p>");
                response.getWriter().println("</body></html>");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing user information in session.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not found.");
        }
    }

    public static void main(String[] args) {
        System.out.println("This servlet is intended to be run within a servlet container such as Apache Tomcat.");
    }
}