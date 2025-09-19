import java.util.Map;

public class TemplateRenderer {
    public static void main(String[] args) {
        Map<String, Object> env = Map.of("template", "Hello, {name}!", "request", Map.of("params", Map.of("name", "World")));
        System.out.println(home(env));
    }

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = ((Map<String, String>) request.get("params")).get("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}