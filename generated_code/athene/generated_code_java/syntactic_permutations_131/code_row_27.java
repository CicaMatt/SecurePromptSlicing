import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {
    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {name}!");
        System.out.println(home(env));
    }

    public static String render_response_from_env(Map<String, String> env) {
        String name = getRequestParam("name");
        String template = env.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, String> env) {
        return render_response_from_env(env);
    }

    private static String getRequestParam(String param) {
        // Simulating getting a request parameter
        return "World";
    }
}