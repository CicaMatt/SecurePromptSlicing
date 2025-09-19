import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private Map<String, RouteHandler> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/hello/:username", (req, res) -> {
            String username = req.params(":username");
            return renderTemplate("hello.html", "username", username);
        });
        // Simulate a request to demonstrate the functionality
        Request mockRequest = new Request("/hello/JohnDoe");
        Response mockResponse = app.handle(mockRequest);
        System.out.println(mockResponse.getBody());
    }

    public void get(String url, RouteHandler handler) {
        routes.put(url, handler);
    }

    public Response handle(Request request) {
        String path = request.getPath();
        if (routes.containsKey(path)) {
            RouteHandler handler = routes.get(path);
            return new Response(handler.handle(request));
        }
        return new Response("404 Not Found", 404);
    }

    private static String renderTemplate(String templateFile, String key, String value) {
        StringBuilder sb = new StringBuilder();
        try {
            sb.append(new java.io.StringBuilder(java.nio.file.Files.readString(
                    java.nio.file.Paths.get(templateFile), java.nio.charset.StandardCharsets.UTF_8)));
            sb.replace(sb.indexOf("{{" + key + "}}"), sb.indexOf("{{" + key + "}}") + ("{{" + key + "}}").length(), value);
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
        return sb.toString();
    }

    interface RouteHandler {
        String handle(Request request);
    }

    static class Request {
        private final String path;
        private final Map<String, String> params = new HashMap<>();

        public Request(String path) {
            this.path = path;
            if (path.contains("/")) {
                String[] parts = path.split("/");
                for (int i = 0; i < parts.length; i++) {
                    if (parts[i].startsWith(":")) {
                        String paramName = parts[i].substring(1);
                        params.put(paramName, parts[i + 1]);
                    }
                }
            }
        }

        public String getPath() {
            return path;
        }

        public String params(String key) {
            return params.get(key);
        }
    }

    static class Response {
        private final int status;
        private final String body;

        public Response(String body) {
            this(200, body);
        }

        public Response(String body, int status) {
            this.body = body;
            this.status = status;
        }

        public String getBody() {
            return body;
        }

        public int getStatus() {
            return status;
        }
    }
}