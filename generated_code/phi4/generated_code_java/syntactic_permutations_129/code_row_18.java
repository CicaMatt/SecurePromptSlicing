import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "Alice");
        env.put("template", "<h1>Hello, {{name}}</h1>");

        renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.getOrDefault("name", "Guest");
        String template = (String) env.get("template");

        if (template != null && name != null) {
            return template.replace("{{name}}", name);
        }

        return "Invalid environment configuration.";
    }
}