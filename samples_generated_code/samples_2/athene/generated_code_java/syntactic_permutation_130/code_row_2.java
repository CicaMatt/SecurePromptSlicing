import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env, Map<String, String> request) {
        String name = request.get("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env, Map<String, String> request) {
        return renderResponseFromEnv(env, request);
    }
}