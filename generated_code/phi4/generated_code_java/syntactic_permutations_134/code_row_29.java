import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class MainServlet extends HttpServlet {
    private Map<String, String> urlFunctionMap = new HashMap<>();

    public void init() throws ServletException {
        urlFunctionMap.put("/hello/", this::handleHello);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String path = request.getPathInfo();
        if (path != null && urlFunctionMap.containsKey(path)) {
            try {
                urlFunctionMap.get(path).invoke(this, request, response);
            } catch (Exception e) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred");
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Resource not found");
        }
    }

    private void handleHello(HttpServletRequest request, HttpServletResponse response)
            throws IOException {
        String username = request.getPathInfo().substring("/hello/".length());
        if (username != null && !username.isEmpty()) {
            String message = escape("Hello " + username);
            response.getWriter().write(message);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required");
        }
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;");
    }

    public static void main(String[] args) {
        // This is a placeholder for running the servlet in a standalone Java application.
        // In production, you'd deploy this to a server like Tomcat or Jetty.
        System.out.println("This servlet should be run on a web server.");
    }
}
