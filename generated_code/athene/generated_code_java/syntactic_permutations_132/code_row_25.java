import java.util.HashMap;
import java.util.Map;

interface RouteHandler {
    String handleRequest(Map<String, Object> params);
}

class Router {
    private Map<String, RouteHandler> routes = new HashMap<>();

    void get(String path, RouteHandler handler) {
        routes.put(path, handler);
    }

    String serve(String url, Map<String, Object> params) {
        for (Map.Entry<String, RouteHandler> entry : routes.entrySet()) {
            if (url.startsWith(entry.getKey())) {
                return entry.getValue().handleRequest(params);
            }
        }
        return "404 Not Found";
    }
}

class TemplateEngine {
    String render(String templateName, Map<String, Object> context) {
        StringBuilder result = new StringBuilder();
        try {
            var templateContent = new java.io.StringBuilder();
            var reader = new java.io.BufferedReader(new java.io.FileReader(templateName + ".html"));
            reader.lines().forEach(templateContent::append);
            reader.close();

            String content = templateContent.toString();
            for (Map.Entry<String, Object> entry : context.entrySet()) {
                content = content.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
            }
            result.append(content);
        } catch (Exception e) {
            result.append("Template rendering error");
        }
        return result.toString();
    }
}

public class App {
    public static void main(String[] args) {
        Router router = new Router();
        TemplateEngine templateEngine = new TemplateEngine();

        router.get("/hello/", new RouteHandler() {
            @Override
            public String handleRequest(Map<String, Object> params) {
                Map<String, Object> context = new HashMap<>();
                context.put("username", params.get("username"));
                return templateEngine.render("hello", context);
            }
        });

        // Simulate a request to /hello/John
        Map<String, Object> params = new HashMap<>();
        params.put("username", "John");
        System.out.println(router.serve("/hello/", params));
    }
}