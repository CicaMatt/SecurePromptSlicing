import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class CheckModServlet extends HttpServlet {
    private static final String VALID_USERNAME = "admin";
    private static final String VALID_PASSWORD = "password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (VALID_USERNAME.equals(username) && VALID_PASSWORD.equals(password)) {
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);

        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new CheckModServlet()), "/check_mod");

        server.start();
        server.join();
    }
}