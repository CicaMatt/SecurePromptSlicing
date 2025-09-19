import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, Runnable> urlMapping = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.route("/hello/:username", () -> {
            String username = "world"; // placeholder for actual dynamic value
            System.out.println(app.escape(app.hello(username)));
        });

        // Simulate a request to /hello/John
        app.urlMapping.get("/hello/:username").run();
    }

    public void route(String url, Runnable handler) {
        urlMapping.put(url, handler);
    }

    public String hello(String username) {
        return "Hello " + username;
    }

    public String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}