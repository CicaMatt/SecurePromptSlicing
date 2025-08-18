import java.util.HashMap;
import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> model = new HashMap<>();
        String name = (String) env.getOrDefault("name", "World");
        return String.format("<h1>Hello, %s!</h1>", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }

    public static void main(String[] args) {
        Map<String, Object> env = new HashMap<>();
        env.put("name", "User");
        System.out.println(home(env));
    }
}