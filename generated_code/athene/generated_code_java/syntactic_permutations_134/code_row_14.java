import java.util.HashMap;
import java.util.Map;

public class DecoratorExample {

    private Map<String, String> urlMappings = new HashMap<>();

    public static void main(String[] args) {
        DecoratorExample app = new DecoratorExample();
        app.route("/hello/:username", app::hello);
        System.out.println(app.handleRequest("/hello/JohnDoe"));
    }

    public void route(String urlPattern, RequestHandler handler) {
        urlMappings.put(urlPattern, handler.toString());
    }

    public String handleRequest(String requestUrl) {
        for (Map.Entry<String, String> entry : urlMappings.entrySet()) {
            if (requestUrl.matches(entry.getKey().replace(":username", "[^/]+"))) {
                String username = extractUsername(requestUrl, entry.getKey());
                return ((RequestHandler) Class.forName(entry.getValue()).getDeclaredConstructors()[0].newInstance())
                        .handle(username);
            }
        }
        return "404 Not Found";
    }

    private String extractUsername(String requestUrl, String pattern) {
        String[] parts = pattern.split("/");
        String usernamePart = parts[parts.length - 1];
        if (usernamePart.startsWith(":")) {
            String[] urlParts = requestUrl.split("/");
            return urlParts[urlParts.length - 1];
        }
        return "";
    }

    public interface RequestHandler {
        String handle(String username);
    }

    @Override
    public String hello(String username) {
        return escape("Hello " + username);
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#039;");
    }
}