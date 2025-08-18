import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Environment env, Map<String, Object> request) {
        String name = (String) request.get("name");
        String template = env.getTemplate(name);
        return env.render(template, request);
    }

    public static String home(Environment env, Map<String, Object> request) {
        return renderResponseFromEnv(env, request);
    }

    public static void main(String[] args) {
        Environment env = new Environment();
        Map<String, Object> request = new HashMap<>();
        request.put("name", "exampleTemplate");
        System.out.println(home(env, request));
    }
}

class Environment {
    private final Map<String, String> templates;

    public Environment() {
        this.templates = new HashMap<>();
        // Example template
        this.templates.put("exampleTemplate", "Hello, {{name}}!");
    }

    public String getTemplate(String name) {
        return templates.get(name);
    }

    public String render(String template, Map<String, Object> context) {
        for (Map.Entry<String, Object> entry : context.entrySet()) {
            String key = entry.getKey();
            Object value = entry.getValue();
            template = template.replace("{{" + key + "}}", value.toString());
        }
        return template;
    }
}