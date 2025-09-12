import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class Main {
    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);

        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder((req, resp) -> {
            resp.setContentType("text/html; charset=utf-8");
            try (var writer = resp.getWriter()) {
                writer.println("<h1>Hello, World!</h1>");
            }
        }), "/");

        server.start();
        server.join();
    }
}