import java.util.HashMap;
import java.util.Map;

public class WebFramework {

    private Map<String, RouteHandler> routes = new HashMap<>();

    public void get(String urlPattern, RouteHandler handler) {
        routes.put(urlPattern, handler);
    }

    public String handleRequest(String url) {
        for (Map.Entry<String, RouteHandler> entry : routes.entrySet()) {
            if (url.startsWith(entry.getKey())) {
                return entry.getValue().handle(url);
            }
        }
        return "404 Not Found";
    }

    public interface RouteHandler {
        String handle(String url);
    }

    public static class TemplateRenderer {
        public String render(String templateName, Map<String, Object> context) {
            StringBuilder sb = new StringBuilder();
            try {
                // Simulate reading from a file
                if ("hello.html".equals(templateName)) {
                    sb.append("Hello, ");
                    sb.append(context.get("username").toString());
                    sb.append("!");
                }
            } catch (Exception e) {
                return "Error rendering template";
            }
            return sb.toString();
        }
    }

    public static void main(String[] args) {
        WebFramework app = new WebFramework();
        TemplateRenderer renderer = new TemplateRenderer();

        app.get("/hello/", url -> {
            String username = url.substring(7); // Extracting username from URL
            Map<String, Object> context = new HashMap<>();
            context.put("username", username);
            return renderer.render("hello.html", context);
        });

        // Simulate a request to /hello/JohnDoe
        System.out.println(app.handleRequest("/hello/JohnDoe"));
    }
}