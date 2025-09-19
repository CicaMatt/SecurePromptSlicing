import java.util.Map;
import java.util.HashMap;

public class WebFramework {
    interface Handler {
        String handleRequest(Map<String, String> params);
    }

    static class RouteDecorator {
        private Map<String, Handler> routes = new HashMap<>();

        public void bind(String urlPattern, Handler handler) {
            routes.put(urlPattern, handler);
        }

        public String processRequest(String url) {
            for (Map.Entry<String, Handler> entry : routes.entrySet()) {
                if (url.matches(entry.getKey())) {
                    Map<String, String> params = new HashMap<>();
                    if (entry.getKey().contains("<username>")) {
                        String username = url.replace("/", "");
                        params.put("username", username);
                    }
                    return entry.getValue().handleRequest(params);
                }
            }
            return "404 Not Found";
        }
    }

    static class TemplateRenderer {
        public String render(String templateName, Map<String, String> context) {
            StringBuilder sb = new StringBuilder();
            try {
                // Simulate reading a file
                String templateContent = "<html><body>Welcome, <span>{username}</span></body></html>";
                for (Map.Entry<String, String> entry : context.entrySet()) {
                    templateContent = templateContent.replace("{" + entry.getKey() + "}", entry.getValue());
                }
                sb.append(templateContent);
            } catch (Exception e) {
                sb.append("Error rendering template");
            }
            return sb.toString();
        }
    }

    public static void main(String[] args) {
        RouteDecorator router = new RouteDecorator();
        TemplateRenderer renderer = new TemplateRenderer();

        Handler userHandler = params -> {
            String username = params.get("username");
            Map<String, String> context = new HashMap<>();
            context.put("username", username);
            return renderer.render("user.html", context);
        };

        router.bind("/<username>", userHandler);

        // Simulate a request to /john
        System.out.println(router.processRequest("/john"));
    }
}