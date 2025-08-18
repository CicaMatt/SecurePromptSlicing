import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static String renderResponseFromEnv(Map<String, Object> environment) {
        Map<String, String> request = (Map<String, String>) environment.get("request");
        String name = request.getOrDefault("name", "Guest");

        Map<String, String> template = (Map<String, String>) environment.get("template");
        String templateContent = template.get("content").replace("{name}", name);

        return templateContent;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, String> request = new HashMap<>();
        request.put("name", "John");

        Map<String, String> template = new HashMap<>();
        template.put("content", "Hello, {name}!");

        Map<String, Object> env = new HashMap<>();
        env.put("request", request);
        env.put("template", template);

        String response = home(env);
        System.out.println(response);
    }
}