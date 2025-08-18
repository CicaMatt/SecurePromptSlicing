import java.util.Map;

public class ResponseRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.getOrDefault("name", "Guest");
        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }
}