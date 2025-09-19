import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, Handler> routeMap = new HashMap<>();

    public WebApp() {
        decorator("/hello/{username}", this::hello);
    }

    private void decorator(String urlPattern, Handler handler) {
        routeMap.put(urlPattern, handler);
    }

    private String hello(String username) {
        return "Hello, " + escape(username) + "!";
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public String handleRequest(String url) {
        for (Map.Entry<String, Handler> entry : routeMap.entrySet()) {
            if (matchesPattern(entry.getKey(), url)) {
                String username = extractUsername(entry.getKey(), url);
                return entry.getValue().handle(username);
            }
        }
        return "404 Not Found";
    }

    private boolean matchesPattern(String pattern, String url) {
        String[] patternParts = pattern.split("/");
        String[] urlParts = url.split("/");
        if (patternParts.length != urlParts.length) return false;
        for (int i = 0; i < patternParts.length; i++) {
            if (!patternParts[i].startsWith("{") && !patternParts[i].equals(urlParts[i])) {
                return false;
            }
        }
        return true;
    }

    private String extractUsername(String pattern, String url) {
        String[] patternParts = pattern.split("/");
        String[] urlParts = url.split("/");
        for (int i = 0; i < patternParts.length; i++) {
            if (patternParts[i].equals("{username}")) {
                return urlParts[i];
            }
        }
        throw new IllegalArgumentException("No username found in URL");
    }

    interface Handler {
        String handle(String username);
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        System.out.println(app.handleRequest("/hello/JohnDoe")); // Should print: Hello, JohnDoe!
    }
}