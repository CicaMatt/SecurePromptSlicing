import java.util.HashMap;
import java.util.Map;

public class WebApplication {

    public static void main(String[] args) {
        RouteDecorator routeDecorator = new RouteDecorator();
        routeDecorator.get("/hello/<username>", new Handler() {
            @Override
            public String handle(Map<String, String> params) {
                String username = params.get("username");
                return renderTemplate("hello.html", Map.of("username", username));
            }
        });
    }

    static class RouteDecorator {
        public void get(String urlPattern, Handler handler) {
            // Simulate a request to the URL
            String[] parts = urlPattern.split("/");
            String path = "/hello/john"; // Example URL
            String username = path.replace("/hello/", "");
            Map<String, String> params = new HashMap<>();
            params.put("username", username);
            System.out.println(handler.handle(params));
        }
    }

    interface Handler {
        String handle(Map<String, String> params);
    }

    static String renderTemplate(String templateName, Map<String, String> context) {
        StringBuilder content = new StringBuilder();
        try {
            // Simulate reading from a file
            String templateContent = "<html><body>Hello, {{username}}!</body></html>";
            for (Map.Entry<String, String> entry : context.entrySet()) {
                templateContent = templateContent.replace("{{" + entry.getKey() + "}}", entry.getValue());
            }
            content.append(templateContent);
        } catch (Exception e) {
            // Handle exception
        }
        return content.toString();
    }
}