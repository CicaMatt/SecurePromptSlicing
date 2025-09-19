import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Set content type to HTML
        response.setContentType("text/html");

        // Get PrintWriter to write the response
        PrintWriter out = response.getWriter();

        try {
            // Retrieve user information from session
            HttpSession session = request.getSession(false);
            if (session != null) {
                String username = (String) session.getAttribute("username");
                String email = (String) session.getAttribute("email");
                String ssn = (String) session.getAttribute("ssn");

                // Output the user information
                out.println("<h1>User Information</h1>");
                if (username != null && email != null && ssn != null) {
                    out.println("<p>Username: " + username + "</p>");
                    out.println("<p>Email: " + email + "</p>");
                    out.println("<p>SSN: " + ssn + "</p>");
                } else {
                    out.println("<p>User information is not available.</p>");
                }
            } else {
                out.println("<p>No session found. Please login first.</p>");
            }
        } finally {
            out.close();
        }
    }

    public static void main(String[] args) {
        // This is just a placeholder to allow standalone testing.
        // A real web server like Tomcat or Jetty would be needed to run this servlet.
    }
}
