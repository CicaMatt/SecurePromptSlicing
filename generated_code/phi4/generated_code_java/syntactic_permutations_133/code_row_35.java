import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class WebApp {
    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        // Create a servlet
        MyServlet myServlet = new MyServlet();
        context.addServlet(new ServletHolder(myServlet), "/hello");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    static class MyServlet extends javax.servlet.http.HttpServlet {
        protected void doGet(javax.servlet.http.HttpServletRequest req, javax.servlet.http.HttpServletResponse resp) throws javax.servlet.ServletException, java.io.IOException {
            resp.setContentType("text/html");
            resp.setStatus(200);
            resp.getWriter().println("<h1>Hello, World!</h1>");
        }
    }
}