import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class InfoServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        HttpSession session = req.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String creditCardLast4 = (String) session.getAttribute("creditCardLast4");

            resp.setContentType("text/html");
            resp.getWriter().println("<html><body>");
            resp.getWriter().println("<h1>User Information</h1>");
            resp.getWriter().println("<p>Username: " + username + "</p>");
            resp.getWriter().println("<p>Email: " + email + "</p>");
            resp.getWriter().println("<p>Credit Card Last 4 Digits: " + creditCardLast4 + "</p>");
            resp.getWriter().println("</body></html>");
        } else {
            resp.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Session not found");
        }
    }

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);

        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new InfoServlet()), "/info");

        server.start();
        server.join();
    }
}