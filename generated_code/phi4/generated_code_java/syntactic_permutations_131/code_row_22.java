import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    private static final String TEMPLATE = "<h1>Hello, {{name}}!</h1>";

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> request = new HashMap<>();
        request.put("name", "World");
        env.put("request", request);

        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.getOrDefault("name", "Guest");

        String renderedTemplate = TEMPLATE.replace("{{name}}", name);

        return createdResponse(renderedTemplate);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    private static String createdResponse(String content) {
        return "HTTP/1.1 200 OK\nContent-Length: " + content.length() + "\n\n" + content;
    }
}