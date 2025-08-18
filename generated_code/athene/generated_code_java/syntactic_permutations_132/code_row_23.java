import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private Map<String, RouteHandler> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            return render("hello.html", Map.of("username", username));
        });
        app.start();
    }

    public void get(String urlPattern, RouteHandler handler) {
        routes.put(urlPattern, handler);
    }

    public void start() {
        // Simulate a request for demonstration purposes
        Request req = new Request("/hello/John");
        Response res = new Response();
        String route = findRoute(req.getPath());
        if (route != null) {
            RouteHandler handler = routes.get(route);
            System.out.println(handler.handle(req, res));
        }
    }

    private String findRoute(String path) {
        return routes.keySet().stream()
                .filter(path::matches)
                .findFirst()
                .orElse(null);
    }

    private static String render(String templateName, Map<String, Object> model) {
        StringBuilder content = new StringBuilder();
        try {
            // Simulate reading from a file
            String templateContent = """
                <html>
                <body>
                    Hello, {{username}}!
                </body>
                </html>
                """;
            for (Map.Entry<String, Object> entry : model.entrySet()) {
                templateContent = templateContent.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
            }
            content.append(templateContent);
        } catch (Exception e) {
            content.append("<h1>Error rendering template</h1>");
        }
        return content.toString();
    }

    interface RouteHandler {
        String handle(Request req, Response res);
    }

    static class Request {
        private final String path;
        private final Map<String, String> params;

        public Request(String path) {
            this.path = path;
            this.params = extractParams(path);
        }

        public String getPath() {
            return path;
        }

        public String params(String key) {
            return params.get(key);
        }

        private Map<String, String> extractParams(String path) {
            Map<String, String> params = new HashMap<>();
            if (path.matches("/hello/.+")) {
                params.put(":username", path.substring(7));
            }
            return params;
        }
    }

    static class Response {}
}