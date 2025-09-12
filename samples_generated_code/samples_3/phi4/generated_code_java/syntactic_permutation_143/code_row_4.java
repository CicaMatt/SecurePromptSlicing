import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {

    private Map<String, Boolean> subscribedUsers = new HashMap<>();

    @Override
    public void init() throws ServletException {
        super.init();
        // Initialize with some dummy data
        subscribedUsers.put("user1@example.com", true);
        subscribedUsers.put("user2@example.com", true);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String email = request.getParameter("email");
        if (email != null && subscribedUsers.containsKey(email)) {
            // Unsubscribe the user
            subscribedUsers.remove(email);
            
            // Send success message
            response.setContentType("text/html");
            response.getWriter().write("<h1>Unsubscribed successfully!</h1>");
        } else {
            // Email not found in subscription list
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "User is not subscribed.");
        }
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = 
                new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        // Add our servlet to the context
        context.addServlet(new org.eclipse.jetty.servlet.ServletHolder(new UnsubscribeServlet()), "/unsubscribe");

        // Start the server
        server.start();
        server.join();
    }
}


**Note**: This code uses Jetty as an embedded server for demonstration purposes. Make sure you have Jetty's dependencies in your project, or adjust the main method to use a different server setup if required.