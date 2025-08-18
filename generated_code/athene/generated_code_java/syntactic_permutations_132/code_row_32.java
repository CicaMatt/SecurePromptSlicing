import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        RouteDecorator.bind("/hello/<username>", new RequestHandler() {
            @Override
            public String handleRequest(Map<String, String> params) {
                String username = params.get("username");
                return renderTemplate("hello.html", Map.of("username", username));
            }
        });
    }

    static class RouteDecorator {
        private static final Map<String, RequestHandler> routes = new HashMap<>();

        public static void bind(String urlPattern, RequestHandler handler) {
            routes.put(urlPattern, handler);
        }

        public static String route(String url) {
            for (Map.Entry<String, RequestHandler> entry : routes.entrySet()) {
                if (url.matches(entry.getKey().replace("/", "\\/").replace("<username>", "[^/]+"))) {
                    Map<String, String> params = new HashMap<>();
                    String usernamePattern = entry.getKey().replaceAll(".*<(.+)>.*", "$1");
                    String usernameValue = url.replaceAll(".*/([^/]+).*", "$1");
                    params.put(usernamePattern, usernameValue);
                    return entry.getValue().handleRequest(params);
                }
            }
            return "404 Not Found";
        }
    }

    interface RequestHandler {
        String handleRequest(Map<String, String> params);
    }

    private static String renderTemplate(String templateName, Map<String, String> context) {
        StringBuilder content = new StringBuilder();
        try {
            java.nio.file.Path path = java.nio.file.Paths.get(templateName);
            for (String line : java.nio.file.Files.readAllLines(path)) {
                for (Map.Entry<String, String> entry : context.entrySet()) {
                    line = line.replace("{{" + entry.getKey() + "}}", entry.getValue());
                }
                content.append(line).append("\n");
            }
        } catch (Exception e) {
            return "Template not found or error reading template.";
        }
        return content.toString();
    }
}