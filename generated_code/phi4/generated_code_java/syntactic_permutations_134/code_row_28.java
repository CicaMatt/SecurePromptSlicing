import java.util.HashMap;
import java.util.function.Function;

public class UrlMapping {

    public static void main(String[] args) {
        UrlHandler urlHandler = new UrlHandler();
        
        // Define mappings
        urlHandler.map("/hello/:username", username -> hello(username));
        
        // Simulate user navigating to URL
        String response = urlHandler.handleRequest("/hello/JohnDoe");
        System.out.println(response);
    }

    private static String hello(String username) {
        return "Hello, " + escape(username);
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}

class UrlHandler {
    private final HashMap<String, Function<String, String>> urlMap = new HashMap<>();

    public void map(String pattern, Function<String, String> handler) {
        urlMap.put(pattern.replace(":username", "%s"), input -> {
            String[] parts = input.split("/");
            if (parts.length == 3 && pattern.equals("/hello/%s")) {
                return handler.apply(parts[2]);
            }
            throw new IllegalArgumentException("Invalid URL or path");
        });
    }

    public String handleRequest(String url) {
        for (String key : urlMap.keySet()) {
            String[] parts = url.split("/");
            if (key.matches(key.replace("%s", ".*"))) {
                return urlMap.get(key).apply(url);
            }
        }
        throw new IllegalArgumentException("No handler found for URL: " + url);
    }
}