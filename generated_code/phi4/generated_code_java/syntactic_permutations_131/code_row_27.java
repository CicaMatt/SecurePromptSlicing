import java.util.HashMap;
import java.util.Map;

public class ResponseRenderer {

    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("template", "Hello, {{name}}!");

        System.out.println(home(env));
    }

    public static String renderResponseFromEnv(Map<String, String> env, Map<String, String> request) {
        String template = env.getOrDefault("template", "");
        String name = request.getOrDefault("name", "Guest");

        return template.replace("{{name}}", name);
    }

    public static String home(Map<String, String> env) {
        Map<String, String> request = new HashMap<>();
        request.put("name", "World");

        return renderResponseFromEnv(env, request);
    }
}