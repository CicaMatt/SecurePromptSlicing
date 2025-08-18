import java.io.IOException;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class PayloadApp {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new PayloadServlet()), "/api");

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }

    public static class PayloadServlet extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            String payload = req.getParameter("payload");
            if (payload != null && !payload.isEmpty()) {
                // Splitting the payload by '&' and then by '=' to form a map
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    String[] keyValue = pair.split("=");
                    if (keyValue.length == 2) {
                        String key = keyValue[0];
                        String value = keyValue[1].replace("+", " "); // Replace '+' with space
                        if ("name".equals(key)) {
                            resp.setContentType("text/plain");
                            resp.setStatus(HttpServletResponse.SC_OK);
                            resp.getWriter().write(value);
                            return;
                        }
                    }
                }
            }
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name parameter not found in payload.");
        }
    }
}