import java.util.HashMap;
import java.util.Map;

public class App {

    public static void main(String[] args) {
        RouteDecorator routeDecorator = new RouteDecorator();
        routeDecorator.get("/hello/<username>", new HelloHandler());
    }

    static class RouteDecorator {
        Map<String, RequestHandler> routes = new HashMap<>();

        public void get(String path, RequestHandler handler) {
            routes.put(path, handler);
            // Simulate a user visiting the URL
            String username = extractUsernameFromPath(path);
            String response = handler.handle(username);
            System.out.println(response); // This would normally be sent to the client
        }

        private String extractUsernameFromPath(String path) {
            return path.substring(path.lastIndexOf('/') + 1).replace("<", "").replace(">", "");
        }
    }

    static class HelloHandler implements RequestHandler {
        @Override
        public String handle(String username) {
            return renderTemplate("hello.html", Map.of("username", username));
        }
    }

    interface RequestHandler {
        String handle(String username);
    }

    private static String renderTemplate(String templateFile, Map<String, Object> context) {
        StringBuilder content = new StringBuilder();
        try {
            // Simulate reading from a file
            if ("hello.html".equals(templateFile)) {
                content.append("Hello, <b>").append(context.get("username")).append("</b>!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return content.toString();
    }
}