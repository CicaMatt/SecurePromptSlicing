import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
        System.out.println(home());
    }

    private static String renderResponseFromEnv(Map<String, String> env) {
        String name = env.getOrDefault("name", "Guest");
        String template = env.getOrDefault("template", "Hello, %s!");
        return response(template.replace("%s", name));
    }

    private static String home() {
        Map<String, String> env = new HashMap<>();
        env.put("name", "John Doe");
        env.put("template", "Welcome, %s! This is your homepage.");
        return renderResponseFromEnv(env);
    }

    private static String response(String renderedTemplate) {
        return "<html><body>" + renderedTemplate + "</body></html>";
    }
}