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
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");
            if (email != null && ssn != null) {
                response.setContentType("text/plain");
                response.getWriter().write("Email: " + email + "\nSSN: " + ssn);
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("User information not found in session.");
            }
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.getWriter().write("Session not found. Please log in first.");
        }
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);

        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler();
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(org.eclipse.jetty.servlet.ServletHolder.class, InfoServlet.class, "/info");

        server.start();
        server.join();
    }
}
