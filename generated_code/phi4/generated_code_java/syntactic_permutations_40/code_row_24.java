import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssnLast4 = (String) session.getAttribute("ssnLast4");

        if (username == null || email == null || ssnLast4 == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Session data is incomplete.");
            return;
        }

        try (PrintWriter out = response.getWriter()) {
            response.setContentType("text/html");
            out.println("<html>");
            out.println("<head><title>User Info</title></head>");
            out.println("<body>");
            out.println("<h1>User Information</h1>");
            out.println("<p>Username: " + username + "</p>");
            out.println("<p>Email: " + email + "</p>");
            out.println("<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>");
            out.println("</body>");
            out.println("</html>");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for demonstration purposes.
        // To run the servlet, you would need to deploy it in a Java EE container like Tomcat or Jetty.
    }
}


To make this code runnable:
1. Ensure you have a Java EE environment set up (e.g., Apache Tomcat).
2. Package this servlet into a web application archive (WAR) and deploy it on the server.
3. Set up session attributes (`username`, `email`, `ssnLast4`) before accessing `/info`.