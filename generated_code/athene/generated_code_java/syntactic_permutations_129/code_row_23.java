import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {
    public String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");

        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public static void main(String[] args) {
        TemplateRenderer renderer = new TemplateRenderer();
        Map<String, Object> env = new HashMap<>();
        Map<String, Object> request = new HashMap<>();
        request.put("name", "John Doe");
        env.put("request", request);
        env.put("template", "Hello, {name}!");

        String response = renderer.render_response_from_env(env);
        System.out.println(response);
    }
}