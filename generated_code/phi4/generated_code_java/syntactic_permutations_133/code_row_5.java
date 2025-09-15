import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class Main {
    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new WSGIApplication()), "/");

        server.start();
        server.join();
    }

    public static class WSGIApplication implements javax.servlet.Servlet {
        @Override
        public void service(javax.servlet.http.HttpServletRequest req, javax.servlet.http.HttpServletResponse resp) throws java.io.IOException {
            String response = "Hello, World!";
            resp.setContentType("text/plain");
            resp.setStatus(javax.servlet.http.HttpServletResponse.SC_OK);
            resp.getWriter().write(response);
        }
    }
}
