import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebApp {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("request", Map.of("name", "World"));
        env.put("template", "<html><body>Hello, {name}!</body></html>");

        System.out.println(home(env));
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.getOrDefault("name", "Guest");

        String template = (String) env.get("template");
        String renderedTemplate = template.replace("{name}", name);

        return createResponse(renderedTemplate);
    }

    public static String createResponse(String content) {
        return "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n" + content;
    }
}