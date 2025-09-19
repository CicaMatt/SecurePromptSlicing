import java.util.HashMap;
import java.util.Map;

interface RouteHandler {
    String handleRequest(String url);
}

class TemplateEngine {
    public String render(String templateName, Map<String, Object> context) {
        StringBuilder sb = new StringBuilder();
        try {
            var templateContent = new java.io.StringBuilder("<html><body>Welcome, <span id='username'>{{username}}</span>!</body></html>");
            String placeholder = "{{" + "username" + "}}";
            String usernameValue = (String) context.get("username");
            sb.append(templateContent.toString().replace(placeholder, usernameValue));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return sb.toString();
    }
}

class Router {
    private Map<String, RouteHandler> routes = new HashMap<>();

    public void get(String path, RouteHandler handler) {
        routes.put(path, handler);
    }

    public String handleRequest(String url) {
        for (Map.Entry<String, RouteHandler> entry : routes.entrySet()) {
            if (url.matches(entry.getKey())) {
                return entry.getValue().handleRequest(url);
            }
        }
        return "404 Not Found";
    }
}

public class App {
    private static final TemplateEngine templateEngine = new TemplateEngine();

    public static void main(String[] args) {
        Router router = new Router();
        
        router.get("/(.*)", (url) -> {
            String username = url.substring(1);
            Map<String, Object> context = new HashMap<>();
            context.put("username", username);
            return templateEngine.render("template.html", context);
        });

        // Simulate a request
        System.out.println(router.handleRequest("/john"));
    }
}