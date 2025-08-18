import java.util.HashMap;
import java.util.Map;

public class WebApp {
    private Map<String, Handler> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            return renderTemplate("hello.html", Map.of("username", username));
        });
        // Simulate a request
        Request req = new Request(Map.of(":username", "John Doe"));
        Response res = app.handle(req);
        System.out.println(res.body());
    }

    public void get(String path, Handler handler) {
        routes.put(path, handler);
    }

    public Response handle(Request request) {
        String path = findMatchingPath(request.path());
        if (path != null) {
            Handler handler = routes.get(path);
            return handler.handle(request);
        }
        return new Response(404, "Not Found");
    }

    private String findMatchingPath(String path) {
        for (String route : routes.keySet()) {
            if (route.matches("/hello/:[^/]+") && path.startsWith("/hello/")) {
                return route;
            }
        }
        return null;
    }

    private static String renderTemplate(String templateName, Map<String, Object> context) {
        StringBuilder sb = new StringBuilder();
        try {
            switch (templateName) {
                case "hello.html":
                    sb.append("<html><body><h1>Hello, ");
                    sb.append(context.get("username").toString());
                    sb.append("</h1></body></html>");
                    break;
                default:
                    throw new IllegalArgumentException("Unknown template: " + templateName);
            }
        } catch (Exception e) {
            return "Error rendering template: " + e.getMessage();
        }
        return sb.toString();
    }

    interface Handler {
        Response handle(Request request);
    }

    static class Request {
        private final Map<String, String> params;

        public Request(Map<String, String> params) {
            this.params = params;
        }

        public String path() {
            return params.get(":username").isEmpty() ? "/hello/" : "/hello/" + params.get(":username");
        }

        public String params(String key) {
            return params.get(key);
        }
    }

    static class Response {
        private final int status;
        private final String body;

        public Response(int status, String body) {
            this.status = status;
            this.body = body;
        }

        public String body() {
            return body;
        }
    }
}