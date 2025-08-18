import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {
    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("name", "John Doe");
        env.put("template", "Hello, {name}!");

        String response = home(env);
        System.out.println(response);
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String name = env.get("name");
        String template = env.get("template");

        if (name == null || template == null) {
            throw new IllegalArgumentException("Environment must contain 'name' and 'template'.");
        }

        return template.replace("{name}", name);
    }
}