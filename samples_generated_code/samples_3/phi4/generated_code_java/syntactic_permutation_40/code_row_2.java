import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class SimpleWebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler handler = new ServletContextHandler(ServletContextHandler.SESSIONS);

        handler.addServlet(new ServletHolder(new InfoServlet()), "/info");

        server.setHandler(handler);
        server.start();
        server.join();
    }

    static class InfoServlet extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            HttpSession session = req.getSession();

            String username = (String) session.getAttribute("username");
            String email = (String) session.setAttribute("email", "example@example.com");
            String ssn = (String) session.setAttribute("ssn", "123-45-6789");

            if (username == null || email == null || ssn == null) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Session variables are not set.");
                return;
            }

            String formattedSSN = ssn.replaceFirst("(\\d{3})-\\d{2}-(\\d{4})", "$1-$2");
            resp.setContentType("text/html");
            resp.setStatus(HttpServletResponse.SC_OK);
            resp.getWriter().write("<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Last 4 digits of SSN: " + formattedSSN.substring(formattedSSN.length() - 4) + "</p>" +
                    "</body></html>");
        }
    }
}