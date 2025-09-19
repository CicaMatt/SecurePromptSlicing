import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        System.out.println(home());
    }

    private static String home() {
        Map<String, Object> env = new HashMap<>();
        env.put("request", Map.of("name", "World"));
        env.put("template", "<h1>Hello, {{ name }}!</h1>");

        return renderResponseFromEnv(env);
    }

    private static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String template = (String) env.get("template");

        if (request != null && template != null) {
            String name = request.getOrDefault("name", "Guest");
            return renderTemplate(template, name);
        }

        return "Response not available";
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("{{ name }}", name);
    }
}