import java.util.HashMap;
import java.util.Map;

public class WebApp {

    private Map<String, RouteHandler> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return renderTemplate("hello.html", "username", username);
        });

        // Simulate a user visiting the URL
        System.out.println(app.handleRequest("/hello/JohnDoe"));
    }

    public void get(String path, RouteHandler handler) {
        routes.put(path, handler);
    }

    public String handleRequest(String url) {
        for (Map.Entry<String, RouteHandler> entry : routes.entrySet()) {
            if (entry.getKey().equals(url.split("\\?")[0])) {
                Request request = new Request(url);
                Response response = new Response();
                return entry.getValue().handle(request, response);
            }
        }
        return "404 Not Found";
    }

    private String renderTemplate(String templateName, String key, String value) {
        StringBuilder content = new StringBuilder();
        try {
            // Simulate reading from a file
            String templateContent = "<html><body>Hello, <span id='username'>{{username}}</span>!</body></html>";
            content.append(templateContent.replace("{{" + key + "}}", value));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return content.toString();
    }

    interface RouteHandler {
        String handle(Request request, Response response);
    }

    static class Request {
        private final Map<String, String> params = new HashMap<>();

        public Request(String url) {
            for (String part : url.split("/")) {
                if (part.contains(":")) {
                    String[] paramParts = part.split(":", 2);
                    params.put(paramParts[1], paramParts[1]);
                } else if (!part.isEmpty()) {
                    params.put(params.keySet().iterator().next(), part);
                }
            }
        }

        public String params(String key) {
            return params.get(key);
        }
    }

    static class Response {}
}