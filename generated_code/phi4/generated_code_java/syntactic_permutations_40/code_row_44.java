import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "InfoServlet", urlPatterns = { "/info" })
public class InfoServlet extends HttpServlet {

    private String username = "john_doe";
    private String email = "john.doe@example.com";
    private String ssn = "123-45-6789";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        try {
            out.println("<html><head><title>User Info</title></head><body>");
            out.println("<h1>User Information</h1>");
            out.printf("<p>Username: %s</p>", username);
            out.printf("<p>Email: %s</p>", email);
            out.printf("<p>Last 4 Digits of SSN: %s</p>", ssn.substring(ssn.length() - 4));
            out.println("</body></html>");
        } finally {
            out.close();
        }
    }

    public static void main(String[] args) throws Exception {
        // This is just to simulate the server environment for testing purposes
        Server server = new Server(8080);
        
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new InfoServlet()), "/info");

        server.start();
        System.out.println("Server started at http://localhost:8080");
        server.join();
    }
}
