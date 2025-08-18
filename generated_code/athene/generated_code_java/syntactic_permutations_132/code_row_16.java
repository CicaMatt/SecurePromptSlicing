import java.util.Map;
import java.util.HashMap;

public class WebApp {

    private Map<String, Handler> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/hello/:username", app::hello);
        app.handleRequest("/hello/John"); // Simulate a request for testing
    }

    public void get(String path, Handler handler) {
        routes.put(path, handler);
    }

    public void handleRequest(String url) {
        String[] parts = url.split("/");
        String username = parts[parts.length - 1];
        String path = "/hello/:username";
        if (routes.containsKey(path)) {
            routes.get(path).handle(username);
        }
    }

    public String renderTemplate(String username) {
        return "Hello, " + username + "!";
    }

    public void hello(String username) {
        System.out.println(renderTemplate(username));
    }

    @FunctionalInterface
    interface Handler {
        void handle(String param);
    }
}