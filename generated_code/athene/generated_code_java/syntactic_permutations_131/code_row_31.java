import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {

    public String render_response_from_env(Map<String, Object> environment) {
        Map<String, String> request = (Map<String, String>) environment.get("request");
        String name = request.getOrDefault("name", "Guest");
        String template = (String) environment.get("template");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> environment) {
        return render_response_from_env(environment);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        Map<String, String> request = new HashMap<>();
        request.put("name", "John Doe");
        env.put("request", request);
        env.put("template", "Hello, {name}!");

        TemplateRenderer renderer = new TemplateRenderer();
        System.out.println(renderer.home(env));
    }
}