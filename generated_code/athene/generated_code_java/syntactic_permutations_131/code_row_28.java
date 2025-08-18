import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String> userRequest = (Map<String, String>) env.get("user_request");
        String name = userRequest.getOrDefault("name", "Guest");

        Map<String, String> templates = (Map<String, String>) env.get("templates");
        String templateName = (String) env.get("template_name");
        String template = templates.getOrDefault(templateName, "Template not found");

        String renderedTemplate = template.replace("{name}", name);

        return renderedTemplate;
    }

    public static void home() {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> userRequest = new HashMap<>();
        userRequest.put("name", "John Doe");
        env.put("user_request", userRequest);

        Map<String, String> templates = new HashMap<>();
        templates.put("home", "Hello, {name}!");
        env.put("templates", templates);
        env.put("template_name", "home");

        String response = render_response_from_env(env);
        System.out.println(response);
    }

    public static void main(String[] args) {
        home();
    }
}