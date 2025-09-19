import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                response.setContentType("text/html");
                response.getWriter().println("<html><body>");
                response.getWriter().println("<h1>User Information</h1>");
                response.getWriter().println("<p>Username: " + username + "</p>");
                response.getWriter().println("<p>Email: " + email + "</p>");
                response.getWriter().println("<p>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>");
                response.getWriter().println("</body></html>");
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing user information in session.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not found.");
        }
    }

    public static void main(String[] args) throws Exception {
        org.apache.catalina.startup.Tomcat tomcat = new org.apache.catalina.startup.Tomcat();
        tomcat.setPort(8080);

        Context ctx = tomcat.addContext("", null);
        Tomcat.addServlet(ctx, "info", new InfoServlet());
        ctx.addServletMappingDecoded("/info", "info");

        tomcat.start();
        tomcat.getServer().await();
    }
}
