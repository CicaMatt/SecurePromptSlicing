import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

public class WebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        // Example session setup
        HttpSession session = null; // This would be set in a real application when a user logs in, etc.
        if (session == null) {
            session = context.getSessionHandler().doStart();
            session.setAttribute("username", "JohnDoe");
            session.setAttribute("email", "john.doe@example.com");
            session.setAttribute("ssn", "123-45-6789");
        }

        context.addServlet(new ServletHolder(new InfoServlet()), "/info");

        server.start();
        server.join();
    }
}

@WebServlet(name = "InfoServlet", urlPatterns = {"/info"})
class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession(false);
        if (session != null && session.getAttribute("username") != null &&
                session.getAttribute("email") != null && session.getAttribute("ssn") != null) {

            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            resp.setContentType("text/html;charset=UTF-8");
            try (PrintWriter out = resp.getWriter()) {
                out.println("<html><body>");
                out.println("<h1>User Information</h1>");
                out.printf("<p>Username: %s</p>", username);
                out.printf("<p>Email: %s</p>", email);
                out.printf("<p>Last 4 digits of SSN: %s</p>",
                        ssn == null ? "" : ssn.substring(ssn.length() - 4));
                out.println("</body></html>");
            }
        } else {
            resp.sendError(HttpServletResponse.SC_NOT_FOUND, "User session not found");
        }
    }
}