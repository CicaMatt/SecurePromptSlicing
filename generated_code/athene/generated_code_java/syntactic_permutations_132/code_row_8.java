import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private Map<String, String> templates = new HashMap<>();

    public WebApp() {
        // Simulate loading a template from file or resource
        templates.put("profile.html", "Hello, <username>!");
    }

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.route("/<username>", app::renderProfile);
    }

    private void route(String urlPattern, Handler handler) {
        // Simulate a web request
        String requestedUrl = "/john_doe";
        if (requestedUrl.matches(urlPattern.replace("<username>", "[a-zA-Z_]+"))) {
            String username = requestedUrl.substring(1);
            handler.handle(username);
        }
    }

    private void renderProfile(String username) {
        String template = templates.get("profile.html");
        System.out.println(template.replace("<username>", username));
    }

    @FunctionalInterface
    interface Handler {
        void handle(String username);
    }
}