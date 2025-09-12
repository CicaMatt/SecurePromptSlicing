import java.util.HashMap;
import java.util.Map;

class TemplateRenderer {
    public static String render(String template, Map<String, Object> context) {
        for (Map.Entry<String, Object> entry : context.entrySet()) {
            template = template.replace("{{" + entry.getKey() + "}}", entry.getValue().toString());
        }
        return template;
    }
}

public class Main {

    private static String render_response_from_env(Map<String, String> env) {
        String name = env.getOrDefault("REQUEST_PARAMETER_NAME", "Guest");
        String template = env.get("TEMPLATE");

        Map<String, Object> context = new HashMap<>();
        context.put("name", name);

        return TemplateRenderer.render(template, context);
    }

    private static String home(Map<String, String> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        // Example environment setup
        Map<String, String> env = new HashMap<>();
        env.put("REQUEST_PARAMETER_NAME", "John Doe");
        env.put("TEMPLATE", "<h1>Hello, {{name}}!</h1>");

        String response = home(env);
        System.out.println(response);  // Outputs: <h1>Hello, John Doe!</h1>
    }
}