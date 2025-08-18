import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class WebApp {

    private Map<String, Function<String, String>> routes = new HashMap<>();

    public WebApp() {
        decorator("/hello/{username}", this::hello);
    }

    private void decorator(String urlPattern, Function<String, String> handler) {
        routes.put(urlPattern, handler);
    }

    public String hello(String username) {
        return "Hello " + escape(username);
    }

    public String handleRequest(String url) {
        for (Map.Entry<String, Function<String, String>> entry : routes.entrySet()) {
            String pattern = entry.getKey();
            if (pattern.equals(url.substring(0, pattern.length()))) {
                String username = url.substring(pattern.indexOf("{") + 1, pattern.indexOf("}"));
                return entry.getValue().apply(username);
            }
        }
        return "404 Not Found";
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        System.out.println(app.handleRequest("/hello/username"));
    }
}