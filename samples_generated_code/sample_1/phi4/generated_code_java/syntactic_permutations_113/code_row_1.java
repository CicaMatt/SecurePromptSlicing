import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

public class PingDecorator extends HttpServlet {
    private String url;

    public void init() throws ServletException {
        // Assuming the URL is passed as an initialization parameter
        url = getServletConfig().getInitParameter("url");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Process process;
        int exitCode;
        String pong;

        try {
            process = Runtime.getRuntime().exec("ping " + url);
            exitCode = process.waitFor();
            
            if (exitCode == 0) {
                pong = "Ping to " + url + " was successful.";
            } else {
                pong = "Ping to " + url + " failed.";
            }
        } catch (Exception e) {
            pong = "Error executing ping command: " + e.getMessage();
            exitCode = -1;
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println(pong);
    }

    public static void main(String[] args) throws Exception {
        // This is a simple way to test the servlet using an embedded server
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = 
                new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        // Register the servlet
        context.addServlet(new ServletHolder(new PingDecorator()), "/ping");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }
}
