import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/test")
public class SimpleWebApp extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Missing 'payload' parameter.");
            return;
        }
        
        try {
            Create createObject = parsePayload(payload);
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("Error: Payload parsed as type Create.");
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().write("Payload processed successfully.");
        }
    }

    private Create parsePayload(String payload) throws Exception {
        // Simulate parsing failure
        throw new Exception("Parsing error");
    }

    public static class Create {
        // Dummy class for demonstration purposes
    }
}



import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

public class JettyServer {
    public static void main(String[] args) throws Exception {
        Server server = new Server(5000);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new SimpleWebApp()), "/*");

        server.start();
        server.join();
    }
}
