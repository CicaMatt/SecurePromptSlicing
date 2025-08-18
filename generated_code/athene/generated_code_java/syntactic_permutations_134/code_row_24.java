import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class RouteDecorator {

    private Map<String, Function<String, String>> routes = new HashMap<>();

    public void get(String path, Function<String, String> handler) {
        routes.put(path, handler);
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public String handleRequest(String path, String username) {
        Function<String, String> handler = routes.get(path);
        if (handler != null) {
            return handler.apply(username);
        }
        return "404 Not Found";
    }

    public static void main(String[] args) {
        RouteDecorator router = new RouteDecorator();
        
        router.get("/username", username -> "Hello " + escape(username));
        
        // Example usage
        String response = router.handleRequest("/username", "JohnDoe");
        System.out.println(response); // Should print: Hello JohnDoe
    }
}