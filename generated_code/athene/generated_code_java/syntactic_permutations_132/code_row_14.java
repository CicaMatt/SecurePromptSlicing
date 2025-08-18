import java.util.Map;
import java.util.HashMap;

public class WebApp {

    private Map<String, Handler> routes = new HashMap<>();

    public static void main(String[] args) {
        WebApp app = new WebApp();
        app.get("/<username>", (req, res) -> {
            String username = req.params("username");
            return renderTemplate("template.html", "username", username);
        });

        // Simulate a request to demonstrate the decorator
        Request mockRequest = new Request() {{
            put("username", "john_doe");
        }};
        Response mockResponse = app.handle(mockRequest, "/john_doe");
        System.out.println(mockResponse.body);
    }

    public void get(String route, Handler handler) {
        routes.put(route, handler);
    }

    public Response handle(Request request, String path) {
        for (Map.Entry<String, Handler> entry : routes.entrySet()) {
            if (entry.getKey().equals("/<username>") && path.startsWith("/")) {
                String username = path.substring(1);
                return entry.getValue().handle(new Request() {{ put("username", username); }});
            }
        }
        return new Response(404, "Not Found");
    }

    private static String renderTemplate(String templateFile, String key, String value) {
        try {
            StringBuilder content = new StringBuilder();
            for (String line : java.nio.file.Files.readAllLines(java.nio.file.Paths.get(templateFile))) {
                content.append(line.replace("{{" + key + "}}", value));
            }
            return content.toString();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @FunctionalInterface
    public interface Handler {
        Response handle(Request request);
    }

    public static class Request extends HashMap<String, String> {
    }

    public static class Response {
        int status;
        String body;

        public Response(int status, String body) {
            this.status = status;
            this.body = body;
        }
    }
}