import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        System.out.println(home());
    }

    public static String home() {
        Map<String, Object> env = createEnv();
        return renderResponseFromEnv(env);
    }

    private static String renderResponseFromEnv(Map<String, Object> environment) {
        Map<String, String> request = (Map<String, String>) environment.get("request");
        String template = (String) environment.get("template");

        // Simulate rendering the template with data from the request
        String renderedTemplate = template.replace("${name}", request.getOrDefault("name", "Guest"));

        return buildResponse(renderedTemplate);
    }

    private static Map<String, Object> createEnv() {
        Map<String, String> request = Map.of("name", "John Doe");
        return Map.of(
            "request", request,
            "template", "<h1>Welcome, ${name}!</h1>"
        );
    }

    private static String buildResponse(String content) {
        return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + content;
    }
}