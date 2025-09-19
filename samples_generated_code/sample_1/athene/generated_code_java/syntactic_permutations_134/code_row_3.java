import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class DecoratorExample {
    private Map<String, Function<String, String>> routes = new HashMap<>();

    public static void main(String[] args) {
        DecoratorExample app = new DecoratorExample();
        app.route("/<username>", app::helloUser);
        System.out.println(app.handleRequest("/john")); // Example request
    }

    public void route(String urlPattern, Function<String, String> handler) {
        routes.put(urlPattern, handler);
    }

    public String handleRequest(String url) {
        for (Map.Entry<String, Function<String, String>> entry : routes.entrySet()) {
            String pattern = entry.getKey();
            if (pattern.equals(url)) {
                return entry.getValue().apply(extractUsername(url));
            } else if (pattern.matches("^/\\<username>$")) {
                String username = extractUsername(url);
                if (username != null) {
                    return entry.getValue().apply(username);
                }
            }
        }
        return "404 Not Found";
    }

    private String extractUsername(String url) {
        if (url.startsWith("/")) {
            return url.substring(1);
        }
        return null;
    }

    public String helloUser(String username) {
        return "Hello " + escape(username);
    }

    private String escape(String input) {
        return input.replace("<", "&lt;").replace(">", "&gt;");
    }
}