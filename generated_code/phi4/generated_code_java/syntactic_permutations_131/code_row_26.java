import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, String> environment = new HashMap<>();
        environment.put("template", "Hello, ${name}!");

        System.out.println(home(environment));
    }

    public static String renderResponseFromEnv(Map<String, String> env) {
        String requestName = "John Doe"; // Simulating a user-provided name
        String template = env.getOrDefault("template", "");

        return renderTemplate(template, requestName);
    }

    private static String renderTemplate(String template, String name) {
        return template.replace("${name}", name);
    }

    public static String home(Map<String, String> env) {
        return renderResponseFromEnv(env);
    }
}