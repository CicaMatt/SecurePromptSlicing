import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private Map<String, Handler> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.route("/hello/:username", (req, res) -> {
            String username = req.params.get("username");
            return renderTemplate("hello.html", Map.of("username", username));
        });
        // Simulate a request
        System.out.println(app.handleRequest("/hello/JohnDoe"));
    }

    public void route(String urlPattern, Handler handler) {
        routes.put(urlPattern, handler);
    }

    public String handleRequest(String url) {
        for (Map.Entry<String, Handler> entry : routes.entrySet()) {
            Request req = new Request(url);
            if (req.matches(entry.getKey())) {
                return entry.getValue().handle(req);
            }
        }
        return "404 Not Found";
    }

    private static String renderTemplate(String templateName, Map<String, Object> model) {
        StringBuilder content = new StringBuilder();
        try {
            // Simulate reading from a file
            switch (templateName) {
                case "hello.html":
                    content.append("Hello, ");
                    if (model.containsKey("username")) {
                        content.append(model.get("username")).append("!");
                    } else {
                        content.append("Guest!");
                    }
                    break;
                default:
                    content.append("Template not found");
            }
        } catch (Exception e) {
            content.append("Error rendering template: ").append(e.getMessage());
        }
        return content.toString();
    }

    interface Handler {
        String handle(Request req);
    }

    static class Request {
        private final String url;
        private final Map<String, String> params = new HashMap<>();

        public Request(String url) {
            this.url = url;
            parseParams(url);
        }

        private void parseParams(String url) {
            if (url.contains("/")) {
                String[] parts = url.split("/", 2);
                if (parts.length > 1 && parts[1].contains(":")) {
                    params.put("username", parts[1]);
                }
            }
        }

        public boolean matches(String pattern) {
            return url.startsWith(pattern.replace("/:username", ""));
        }

        public Map<String, String> getParams() {
            return params;
        }
    }
}