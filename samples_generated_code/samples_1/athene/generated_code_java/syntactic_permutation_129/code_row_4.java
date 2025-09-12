import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> request) {
        Map<String, Object> env = Map.of(
            "name", request.get("name"),
            "template", "Hello, {name}!"
        );
        return renderResponseFromEnv(env);
    }
}