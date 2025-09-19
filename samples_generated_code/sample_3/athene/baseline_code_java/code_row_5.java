import java.util.HashMap;
import java.util.Map;

interface Route {
    String handleRequest(String requestPath);
}

class Router {
    private Map<String, Route> routes = new HashMap<>();

    public void get(String path, Route route) {
        routes.put(path, route);
    }

    public String dispatch(String url) {
        for (Map.Entry<String, Route> entry : routes.entrySet()) {
            if (url.startsWith(entry.getKey())) {
                return entry.getValue().handleRequest(url.substring(entry.getKey().length()));
            }
        }
        return "404 Not Found";
    }
}

class TemplateRenderer {
    public String render(String templateName, Map<String, String> context) {
        StringBuilder sb = new StringBuilder();
        try {
            switch (templateName) {
                case "hello.html":
                    sb.append("<html><body>");
                    sb.append("Hello, ").append(context.get("username")).append("!");
                    sb.append("</body></html>");
                    break;
                default:
                    throw new IllegalArgumentException("Template not found");
            }
        } catch (Exception e) {
            return "Error rendering template: " + e.getMessage();
        }
        return sb.toString();
    }
}

public class WebApp {
    public static void main(String[] args) {
        Router router = new Router();
        TemplateRenderer renderer = new TemplateRenderer();

        router.get("/hello/", username -> {
            Map<String, String> context = new HashMap<>();
            context.put("username", username);
            return renderer.render("hello.html", context);
        });

        // Simulate a request
        String response = router.dispatch("/hello/JohnDoe");
        System.out.println(response);
    }
}