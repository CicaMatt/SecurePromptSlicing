import java.util.HashMap;
import java.util.Map;

public class WebServer {
    private Map<String, RequestHandler> routeMap = new HashMap<>();

    public interface RequestHandler {
        String handleRequest(String username);
    }

    public void get(String path, RequestHandler handler) {
        routeMap.put(path, handler);
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public static void main(String[] args) {
        WebServer server = new WebServer();
        server.get("/hello/:username", username -> "Hello " + escape(username));
        
        // Simulate a request
        String path = "/hello/John Doe";
        String username = path.substring(path.lastIndexOf("/") + 1);
        RequestHandler handler = server.routeMap.get("/hello/:username");
        if (handler != null) {
            System.out.println(handler.handleRequest(username));
        }
    }
}