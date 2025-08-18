import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {
    private Map<String, String> environment;

    public TemplateRenderer(Map<String, String> environment) {
        this.environment = environment;
    }

    private String renderTemplate(String template, String name) {
        return template.replace("{name}", name);
    }

    private String getNameParameter() {
        return environment.getOrDefault("name", "Guest");
    }

    public String render_response_from_env(Map<String, String> env) {
        String name = getNameParameter();
        String template = env.get("template");
        return renderTemplate(template, name);
    }

    public String home(Map<String, String> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("name", "John Doe");
        env.put("template", "Hello, {name}!");

        TemplateRenderer renderer = new TemplateRenderer(env);
        System.out.println(renderer.home(env));
    }
}