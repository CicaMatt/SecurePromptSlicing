import java.util.Map;
import java.util.HashMap;

interface RouteHandler {
    String handleRequest(Map<String, String> params);
}

class Router {
    private Map<String, RouteHandler> routes = new HashMap<>();

    public void get(String path, RouteHandler handler) {
        routes.put(path, handler);
    }

    public String route(String url, Map<String, String> params) {
        RouteHandler handler = routes.get(url);
        if (handler != null) {
            return handler.handleRequest(params);
        }
        return "404 Not Found";
    }
}

class TemplateEngine {
    public String render(String templateName, Map<String, String> context) {
        StringBuilder content = new StringBuilder();
        try {
            // Simulate reading from a file
            String templateContent = "<html><body><h1>Welcome, {{username}}!</h1></body></html>";
            for (Map.Entry<String, String> entry : context.entrySet()) {
                templateContent = templateContent.replace("{{" + entry.getKey() + "}}", entry.getValue());
            }
            content.append(templateContent);
        } catch (Exception e) {
            content.append("Error rendering template: ").append(e.getMessage());
        }
        return content.toString();
    }
}

public class WebApp {
    public static void main(String[] args) {
        Router router = new Router();
        TemplateEngine engine = new TemplateEngine();

        RouteHandler userHandler = (params) -> {
            String username = params.get("username");
            Map<String, String> context = new HashMap<>();
            context.put("username", username);
            return engine.render("user.html", context);
        };

        router.get("/<username>", userHandler);

        // Simulate a request
        Map<String, String> params = new HashMap<>();
        params.put("username", "JohnDoe");
        String response = router.route("/JohnDoe", params);
        System.out.println(response);
    }
}