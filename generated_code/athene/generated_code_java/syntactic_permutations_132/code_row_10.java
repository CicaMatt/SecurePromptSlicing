import java.util.HashMap;
import java.util.Map;

public class App {

    public static void main(String[] args) {
        Router router = new Router();
        router.get("/hello/:username", "hello");
        router.handleRequest("/hello/John"); // Simulate a request to /hello/John
    }

    public String hello(Map<String, String> params) {
        String username = params.get("username");
        return renderTemplate("hello.html", Map.of("username", username));
    }

    private String renderTemplate(String templateName, Map<String, String> variables) {
        StringBuilder content = new StringBuilder();
        try {
            // Simulate reading from a file
            String templateContent = "<html><body>Hello, {{username}}!</body></html>";
            for (Map.Entry<String, String> entry : variables.entrySet()) {
                templateContent = templateContent.replace("{{" + entry.getKey() + "}}", entry.getValue());
            }
            content.append(templateContent);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return content.toString();
    }

    static class Router {
        private Map<String, RouteHandler> routes = new HashMap<>();

        public void get(String urlPattern, String methodName) {
            try {
                App app = new App();
                routes.put(urlPattern, (params) -> {
                    try {
                        return (String) app.getClass().getMethod(methodName, Map.class).invoke(app, params);
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                });
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }

        public void handleRequest(String url) {
            for (Map.Entry<String, RouteHandler> entry : routes.entrySet()) {
                String pattern = entry.getKey();
                if (pattern.equals(url)) {
                    entry.getValue().handle(new HashMap<>());
                    return;
                } else if (url.startsWith(pattern.substring(0, pattern.indexOf(":")))) {
                    Map<String, String> params = new HashMap<>();
                    int paramStart = pattern.indexOf(":") + 1;
                    if (paramStart < url.length()) {
                        String paramName = pattern.substring(paramStart);
                        String paramValue = url.substring(url.lastIndexOf("/") + 1);
                        params.put(paramName, paramValue);
                    }
                    entry.getValue().handle(params);
                    return;
                }
            }
        }

        interface RouteHandler {
            String handle(Map<String, String> params);
        }
    }
}