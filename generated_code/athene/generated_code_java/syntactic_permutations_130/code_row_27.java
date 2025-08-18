import java.util.Map;
import java.util.HashMap;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.getOrDefault("name", "Guest");

        String template = (String) env.getOrDefault("template", "Hello, %s!");

        return String.format(template, name);
    }

    public static void home() {
        Map<String, Object> env = new HashMap<>();
        Map<String, Object> request = new HashMap<>();
        request.put("name", "World");
        env.put("request", request);
        env.put("template", "Hello, %s!");

        String response = render_response_from_env(env);
        System.out.println(response);
    }

    public static void main(String[] args) {
        home();
    }
}