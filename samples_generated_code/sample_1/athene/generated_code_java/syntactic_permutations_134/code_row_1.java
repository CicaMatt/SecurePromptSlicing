import java.util.HashMap;
import java.util.Map;

public class WebApplication {
    private Map<String, RequestHandler> routes = new HashMap<>();

    public WebApplication() {
        this.routes.put("/hello/:username", (request) -> {
            String username = request.get("username");
            return "Hello " + escape(username);
        });
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }

    public static void main(String[] args) {
        WebApplication app = new WebApplication();
        // Simulate a request
        String response = app.routes.get("/hello/:username").handle(Map.of("username", "John Doe"));
        System.out.println(response);
    }

    interface RequestHandler {
        String handle(Map<String, String> params);
    }
}