import java.util.HashMap;
import java.util.Map;

public class RouteHandler {
    private Map<String, Runnable> routes = new HashMap<>();

    public void get(String url, Runnable handler) {
        routes.put(url, handler);
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public void handleRequest(String url) {
        Runnable handler = routes.get(url);
        if (handler != null) {
            handler.run();
        }
    }

    public static void main(String[] args) {
        RouteHandler router = new RouteHandler();

        String username = "JohnDoe";
        router.get("/hello/" + username, () -> {
            System.out.println("Hello " + escape(username));
        });

        // Simulate a request to /hello/JohnDoe
        router.handleRequest("/hello/JohnDoe");
    }
}