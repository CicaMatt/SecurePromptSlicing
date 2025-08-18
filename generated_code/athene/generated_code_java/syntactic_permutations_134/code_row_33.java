import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, RequestHandler> routes = new HashMap<>();

    public interface RequestHandler {
        String handleRequest(String... params);
    }

    public void get(String path, RequestHandler handler) {
        routes.put(path, handler);
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public RequestHandler route(String path) {
        return routes.get(path);
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();

        app.get("/hello/:username", (String... params) -> {
            String username = params[0];
            return "Hello " + escape(username);
        });

        // Simulate a request to /hello/John
        RequestHandler handler = app.route("/hello/:username");
        if (handler != null) {
            System.out.println(handler.handleRequest("John"));
        }
    }
}