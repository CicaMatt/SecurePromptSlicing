import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> environment) {
        String name = (String) environment.get("name");
        String template = (String) environment.getOrDefault("template", "Hello, %s!");
        return String.format(template, name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "World");
        env.put("template", "Hello, %s!");

        String response = home(env);
        System.out.println(response);
    }
}