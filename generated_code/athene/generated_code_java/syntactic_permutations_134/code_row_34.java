import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class WebApp {
    private Map<String, Function<String, String>> urlMap = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.route("/hello", app::hello);
        System.out.println(app.handleRequest("/hello", "John Doe"));
    }

    public void route(String path, Function<String, String> handler) {
        urlMap.put(path, handler);
    }

    public String handleRequest(String path, String username) {
        if (urlMap.containsKey(path)) {
            return escape(urlMap.get(path).apply(username));
        }
        return "404 Not Found";
    }

    private String hello(String username) {
        return "Hello " + username;
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}