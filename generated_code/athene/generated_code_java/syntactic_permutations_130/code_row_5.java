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

    public static void main(String[] args) {
        Map<String, Object> env = Map.of("template", "Hello, {name}!");
        Map<String, String> request = Map.of("name", "World");
        System.out.println(home(env, request));
    }
}