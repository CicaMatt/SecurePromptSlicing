import java.util.Map;

public class TemplateRenderer {
    public static void main(String[] args) {
        Map<String, String> env = Map.of(
            "name", "John Doe",
            "template", "<html><body><h1>Hello, {{name}}!</h1></body></html>"
        );

        System.out.println(home(env));
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String name = env.get("name");
        String template = env.get("template");

        if (name == null || template == null) {
            throw new IllegalArgumentException("Environment must contain 'name' and 'template'");
        }

        return renderTemplate(template, name);
    }

    public static String renderTemplate(String template, String name) {
        return template.replace("{{name}}", name);
    }
}