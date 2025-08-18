import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        if (username == null || username.trim().isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Hello, guest!");
        } else {
            response.setContentType("text/plain");
            response.getWriter().write("Hello " + username + "!\n");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Assuming the username is sent in the body as a form parameter
        String username = request.getParameter("username");
        if (username == null || username.trim().isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Hello, guest!");
        } else {
            response.setContentType("text/plain");
            response.getWriter().write("Hello " + username + "!\n");
        }
    }

    public static void main(String[] args) throws Exception {
        // This is a simple way to run the servlet without deploying it in a container
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        // Map the servlet
        context.addServlet(new org.eclipse.jetty.servlet.ServletHolder(new HelloServlet()), "/hello");

        // Start the server
        server.start();
        server.join();
    }
}