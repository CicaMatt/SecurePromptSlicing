import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, Runnable> routes = new HashMap<>();

    public void get(String url, Runnable handler) {
        routes.put(url, handler);
    }

    public String escape(String input) {
        return input.replaceAll("&", "&amp;")
                    .replaceAll("<", "&lt;")
                    .replaceAll(">", "&gt;")
                    .replaceAll("\"", "&quot;")
                    .replaceAll("'", "&#039;");
    }

    public void run() {
        get("/hello/:username", () -> {
            String username = "defaultUser"; // This should be replaced with actual logic to extract from URL
            System.out.println("Hello " + escape(username));
        });

        // Simulate a request
        simulateRequest("/hello/JohnDoe");
    }

    private void simulateRequest(String url) {
        if (url.startsWith("/hello/")) {
            String username = url.substring(7); // Extract the username from URL
            System.out.println("Hello " + escape(username));
        }
    }

    public static void main(String[] args) {
        new WebApp().run();
    }
}