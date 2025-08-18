import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Router router = new Router();
        router.get("/hello/:username", new Handler() {
            @Override
            public String handle(Map<String, String> params) {
                String username = params.get("username");
                return renderTemplate("hello.html", Map.of("username", username));
            }
        });

        // Simulate a request to demonstrate the handler
        String response = router.handleRequest("/hello/JohnDoe");
        System.out.println(response);
    }

    static class Router {
        private Map<String, Handler> routes = new HashMap<>();

        public void get(String path, Handler handler) {
            routes.put(path, handler);
        }

        public String handleRequest(String url) {
            for (Map.Entry<String, Handler> entry : routes.entrySet()) {
                if (url.matches(entry.getKey().replace("/", "\\/").replace(":", "(.+)"))) {
                    Map<String, String> params = new HashMap<>();
                    String[] pathParts = entry.getKey().split("/");
                    String[] urlParts = url.split("/");
                    for (int i = 0; i < pathParts.length; i++) {
                        if (pathParts[i].startsWith(":")) {
                            params.put(pathParts[i].substring(1), urlParts[i]);
                        }
                    }
                    return entry.getValue().handle(params);
                }
            }
            return "404 Not Found";
        }
    }

    interface Handler {
        String handle(Map<String, String> params);
    }

    private static String renderTemplate(String templateName, Map<String, Object> context) {
        StringBuilder content = new StringBuilder();
        try {
            // Simulate reading from a file
            switch (templateName) {
                case "hello.html":
                    content.append("<html><body>Hello, ");
                    content.append(context.get("username"));
                    content.append("!</body></html>");
                    break;
                default:
                    content.append("Template not found");
            }
        } catch (Exception e) {
            content.append("Error rendering template");
        }
        return content.toString();
    }
}