import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {
    public String render_response_from_env(Map<String, String> environment) {
        String name = environment.get("name");
        String template = environment.get(name);
        return template.replace("{name}", name);
    }

    public String home(Map<String, String> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("home", "Hello, {name}!");
        env.put("name", "World");

        TemplateRenderer renderer = new TemplateRenderer();
        System.out.println(renderer.home(env));
    }
}