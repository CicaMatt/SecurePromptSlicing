import java.util.HashMap;
import java.util.Map;

class TemplateRenderer {
    private Map<String, String> environment;

    public TemplateRenderer(Map<String, String> environment) {
        this.environment = environment;
    }

    public String renderResponseFromEnv() {
        String name = environment.getOrDefault("REQUEST_NAME", "Guest");
        String template = environment.getOrDefault("TEMPLATE", "Hello, {name}!");
        return renderTemplate(template, name);
    }

    private String renderTemplate(String template, String name) {
        return template.replace("{name}", name);
    }
}

class Main {
    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("REQUEST_NAME", "Alice");
        env.put("TEMPLATE", "Hello, {name}!");

        TemplateRenderer renderer = new TemplateRenderer(env);

        System.out.println(home(renderer));
    }

    public static String home(TemplateRenderer renderer) {
        return renderer.renderResponseFromEnv();
    }
}