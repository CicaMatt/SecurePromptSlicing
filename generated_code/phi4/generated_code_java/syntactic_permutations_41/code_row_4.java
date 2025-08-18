import com.fasterxml.jackson.databind.ObjectMapper;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebApplication {

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        
        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new InfoServlet()), "/info");

        server.start();
        server.join();
    }

    public static class InfoServlet extends HttpServlet {
        private final Map<String, User> users = new HashMap<>();

        public InfoServlet() {
            // Dummy user data
            users.put("john_doe", new User("John Doe", "john@example.com", "123-45-6789"));
            users.put("jane_smith", new User("Jane Smith", "jane@example.com", "987-65-4321"));
        }

        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            String username = req.getParameter("username");
            if (username == null || !users.containsKey(username)) {
                resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                resp.getWriter().write("Invalid or missing username.");
                return;
            }
            
            User user = users.get(username);

            Map<String, Object> responseMap = new HashMap<>();
            responseMap.put("username", user.getUsername());
            responseMap.put("email", user.getEmail());
            responseMap.put("ssnLast4", user.getSsn().substring(user.getSsn().length() - 4));

            ObjectMapper mapper = new ObjectMapper();
            String jsonResponse = mapper.writeValueAsString(responseMap);

            resp.setContentType("application/json");
            resp.getWriter().write(jsonResponse);
        }
    }

    public static class User {
        private final String username;
        private final String email;
        private final String ssn;

        public User(String username, String email, String ssn) {
            this.username = username;
            this.email = email;
            this.ssn = ssn;
        }

        public String getUsername() {
            return username;
        }

        public String getEmail() {
            return email;
        }

        public String getSsn() {
            return ssn;
        }
    }
}