import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class WebApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new MyServlet()), "/myurl");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    public static class MyServlet extends javax.servlet.http.HttpServlet {
        protected void doGet(javax.servlet.http.HttpServletRequest req, javax.servlet.http.HttpServletResponse resp) throws javax.servlet.ServletException, java.io.IOException {
            resp.setContentType("text/plain");
            resp.getWriter().println("Hello, user!");
        }
    }
}
