import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {

    private final HashMap<String, Runnable> routeMap = new HashMap<>();

    @Override
    public void init() throws ServletException {
        routeMap.put("username", this::handleHello);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String[] pathParts = request.getPathInfo().split("/");
        
        if (pathParts.length == 2 && "username".equals(pathParts[1])) {
            Runnable handler = routeMap.get("username");
            if (handler != null) {
                handler.run();
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void handleHello() throws IOException {
        String username = request.getParameter("username");
        if (username == null || username.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username parameter is required.");
            return;
        }
        
        String safeUsername = escape(username);

        response.setContentType("text/plain");
        response.getWriter().write("Hello, " + safeUsername);
    }

    private String escape(String input) {
        if (input == null) return null;
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;");
    }
}