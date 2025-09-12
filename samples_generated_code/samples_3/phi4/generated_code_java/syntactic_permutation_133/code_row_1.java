import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class WebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        // The second line creates the servlet mapping
        context.addServlet(new ServletHolder(new MyServlet()), "/hello");

        try {
            // The sixth line runs the application
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    private static class MyServlet extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            // The fifth line returns the message to the user
            resp.setContentType("text/plain");
            resp.setStatus(HttpServletResponse.SC_OK);
            resp.getWriter().println("Hello, World!");
        }
    }
}