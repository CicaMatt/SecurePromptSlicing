import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Router router = new Router();
        router.get("/hello/:username", "hello");
        
        // Simulate a user visiting /hello/John
        String response = router.handleRequest("/hello/John");
        System.out.println(response);
    }

    static class Router {
        Map<String, RouteHandler> routes = new HashMap<>();

        public void get(String path, String handlerName) {
            RouteHandler handler;
            if ("hello".equals(handlerName)) {
                handler = this::handleHello;
            } else {
                throw new IllegalArgumentException("Unknown handler: " + handlerName);
            }
            routes.put(path, handler);
        }

        public String handleRequest(String url) {
            for (Map.Entry<String, RouteHandler> entry : routes.entrySet()) {
                if (url.matches(entry.getKey().replace("/", "\\/").replace(":", "[^/]+"))) {
                    return entry.getValue().handle(url);
                }
            }
            return "404 Not Found";
        }

        private String handleHello(String url) {
            String username = extractUsername(url);
            return renderTemplate("hello.html", Map.of("username", username));
        }

        private String extractUsername(String url) {
            int start = url.lastIndexOf('/') + 1;
            return url.substring(start);
        }

        private String renderTemplate(String templateName, Map<String, Object> context) {
            StringBuilder sb = new StringBuilder();
            if ("hello.html".equals(templateName)) {
                sb.append("<html><body>");
                sb.append("Hello, ");
                sb.append(context.get("username"));
                sb.append("!");
                sb.append("</body></html>");
            }
            return sb.toString();
        }
    }

    interface RouteHandler {
        String handle(String url);
    }
}