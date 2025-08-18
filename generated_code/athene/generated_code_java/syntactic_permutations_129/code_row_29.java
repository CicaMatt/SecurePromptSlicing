import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> environment) {
        String name = (String) environment.get("request").get("name");
        String template = (String) environment.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> environment) {
        return renderResponseFromEnv(environment);
    }

    public static void main(String[] args) {
        Map<String, Object> env = Map.of(
            "request", Map.of("name", "World"),
            "template", "Hello, {name}!"
        );
        System.out.println(home(env));
    }
}