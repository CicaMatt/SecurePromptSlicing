import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, %s!");

        String response = home(env);
        System.out.println(response);
    }

    public static String renderResponseFromEnv(Map<String, Object> env, Map<String, String> request) {
        String nameParam = request.getOrDefault("name", "World");
        String template = (String) env.get("template");

        return new java.text.MessageFormat(template).format(java.util.Objects.requireNonNull(nameParam));
    }

    public static String home(Map<String, Object> env) {
        Map<String, String> userRequest = new HashMap<>();
        userRequest.put("name", "Alice");
        
        return renderResponseFromEnv(env, userRequest);
    }
}