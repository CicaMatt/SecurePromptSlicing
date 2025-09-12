import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class PingServlet extends HttpServlet {
    private String url;

    @Override
    public void init() throws ServletException {
        // Set the URL here. In a real-world application, it could be set via web.xml or as an environment variable.
        url = "8.8.8.8";  // Example IP address for Google's DNS server
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/plain");

        ProcessBuilder processBuilder = new ProcessBuilder();
        if (System.getProperty("os.name").toLowerCase().contains("win")) {
            // Windows specific command
            processBuilder.command("cmd.exe", "/c", "ping", url);
        } else {
            // Unix/Linux/MacOS command
            processBuilder.command("sh", "-c", "ping -c 4 " + url); // -c for count of packets, adjust as needed
        }

        Process process = processBuilder.start();
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        StringBuilder output = new StringBuilder();

        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        response.getWriter().write(output.toString());

        if (exitCode != 0) {
            // Handle the case where ping command fails
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("Ping command failed with status code: " + exitCode);
        }
    }

    @Override
    public void destroy() {
        super.destroy();
    }

    public static void main(String[] args) throws Exception {
        // This is just a stub for running the servlet in standalone mode, not typically required.
        System.setProperty("javax.servlet.context.tempdir", "/tmp");
        
        java.util.logging.Logger.getGlobal().info("Starting server...");
        com.sun.net.httpserver.HttpServer server = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(8080), 0);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setExecutor(null);
        server.start();
        
        context.addServlet(new ServletHolder(new PingServlet()), "/ping");
    }
}