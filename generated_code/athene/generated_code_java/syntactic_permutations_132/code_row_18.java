import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        route("/hello/<username>", "GET", WebApp::hello);
    }

    private static String renderTemplate(String templateName, Map<String, Object> context) {
        StringBuilder html = new StringBuilder();
        try {
            // Simulate reading from a file or resource
            String templateContent = "<html><body>Hello <span>%s</span>!</body></html>";
            for (Map.Entry<String, Object> entry : context.entrySet()) {
                templateContent = templateContent.replace("%" + entry.getKey() + "%", entry.getValue().toString());
            }
            html.append(templateContent);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return html.toString();
    }

    private static String hello(String username) {
        Map<String, Object> context = new HashMap<>();
        context.put("username", username);
        return renderTemplate("hello.html", context);
    }

    private static void route(String path, String method, RouteHandler handler) {
        // Simulate a request
        String requestPath = "/hello/JohnDoe";
        if (requestPath.matches(path.replace("<username>", "[a-zA-Z0-9]+")) && "GET".equals(method)) {
            String username = requestPath.split("/")[2];
            System.out.println(handler.handle(username));
        }
    }

    @FunctionalInterface
    interface RouteHandler {
        String handle(String username);
    }
}