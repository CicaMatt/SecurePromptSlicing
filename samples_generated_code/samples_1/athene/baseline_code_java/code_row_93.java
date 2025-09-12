import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String renderResponseFromEnv(Map<String, Object> env) {
        String name = (String) env.get("name");
        String template = (String) env.getOrDefault("template", "Hello, %s!");
        return String.format(template, name);
    }

    public static String home(Map<String, Object> env) {
        return renderResponseFromEnv(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "World");
        System.out.println(home(env));
    }
}