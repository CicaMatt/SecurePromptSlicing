import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {
    public String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "John Doe");
        env.put("template", "Hello, {name}!");
        
        TemplateRenderer renderer = new TemplateRenderer();
        String response = renderer.home(env);
        System.out.println(response);
    }
}