import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(".*example\\.com.*")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }

    public static void main(String[] args) {
        // Main method to launch the server for testing purposes
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);

        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        org.eclipse.jetty.servlet.ServletHolder holder = new org.eclipse.jetty.servlet.ServletHolder(new RedirectServlet());
        context.addServlet(holder, "/redirect");

        try {
            server.start();
            server.join();
        } catch (Exception e) {
            e.printStackTrace(System.err);
        }
    }
}
