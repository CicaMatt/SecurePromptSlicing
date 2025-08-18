import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");

        if (name == null || template == null) {
            return "Missing parameters";
        }

        String renderedTemplate = template.replace("{name}", name);
        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = Map.of(
            "name", "World",
            "template", "Hello, {name}!"
        );

        System.out.println(home(env));
    }
}