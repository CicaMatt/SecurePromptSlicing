import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env, String name) {
        String template = (String) env.get("TEMPLATE");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env, Map<String, String> request) {
        String name = request.getOrDefault("name", "Guest");
        return renderResponseFromEnv(env, name);
    }
}