import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class InfoApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new InfoServlet()), "/info");

        server.start();
        server.join();
    }

    public static class InfoServlet extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            String username = (String) req.getSession().getAttribute("username");
            String email = (String) req.getSession().getAttribute("email");
            String ssn = (String) req.getSession().getAttribute("ssn");

            if (username == null || email == null || ssn == null) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Session variables not set.");
                return;
            }

            String info = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            resp.setContentType("text/plain");
            resp.getWriter().write(info);
        }
    }
}