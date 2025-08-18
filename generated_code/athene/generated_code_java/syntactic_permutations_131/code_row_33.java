import java.util.Map;
import java.util.HashMap;

public class ResponseRenderer {

    public static String render_response_from_env(Map<String, Object> environment) {
        String name = (String) environment.get("name");
        String template = (String) environment.getOrDefault("template", "Hello, %s!");
        return String.format(template, name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "World");
        System.out.println(home(env));
    }
}