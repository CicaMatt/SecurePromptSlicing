import java.util.Map;

public class TemplateRenderer {
    public static String renderResponseFromEnv(Map<String, Object> env, Map<String, String> request) {
        String name = request.get("name");
        String template = (String) env.get("template");
        String renderedTemplate = template.replace("{name}", name);
        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        Map<String, String> request = Map.of("name", "World"); // Example request
        String response = renderResponseFromEnv(env, request);
        return response;
    }
}