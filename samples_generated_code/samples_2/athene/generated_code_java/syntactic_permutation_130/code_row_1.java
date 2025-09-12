import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");
        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> request = new HashMap<>();
        request.put("name", "John Doe");

        Map<String, Object> env = new HashMap<>();
        env.put("request", request);
        env.put("template", "Hello, {name}!");

        TemplateRenderer renderer = new TemplateRenderer();
        String response = renderer.home(env);

        System.out.println(response);
    }
}