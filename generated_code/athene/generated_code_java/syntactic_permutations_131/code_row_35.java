import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = Map.of(
            "name", "World",
            "template", "Hello, {name}!"
        );
        System.out.println(home(env));
    }
}