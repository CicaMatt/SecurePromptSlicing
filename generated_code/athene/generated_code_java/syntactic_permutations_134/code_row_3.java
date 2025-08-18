import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class WebApp {

    private Map<String, Function<String, String>> urlMap = new HashMap<>();

    public WebApp() {
        decorator("/hello/{username}", this::hello);
    }

    private void decorator(String urlPattern, Function<String, String> handler) {
        urlMap.put(urlPattern, handler);
    }

    public String hello(String username) {
        return "Hello " + escape(username);
    }

    public String routeRequest(String url) {
        for (String pattern : urlMap.keySet()) {
            if (url.startsWith(pattern.replace("{username}", ""))) {
                String username = url.substring("/hello/".length());
                return urlMap.get(pattern).apply(username);
            }
        }
        return "404 Not Found";
    }

    private String escape(String input) {
        return input.replaceAll("&", "&amp;")
                    .replaceAll("<", "&lt;")
                    .replaceAll(">", "&gt;")
                    .replaceAll("\"", "&quot;")
                    .replaceAll("'", "&#39;");
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        System.out.println(app.routeRequest("/hello/John Doe")); // Should print: Hello John Doe
    }
}