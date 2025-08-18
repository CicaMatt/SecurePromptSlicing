import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class Main {
    public static void main(String[] args) {
        Map<String, String> env = new HashMap<>();
        env.put("name", "World");
        env.put("template", "<h1>Hello, ${name}!</h1>");

        System.out.println(home(env));
    }

    public static String render_response_from_env(Map<String, String> env) {
        String name = env.getOrDefault("name", "Guest");
        String templateStr = env.getOrDefault("template", "<h1>Hello, ${name}!</h1>");
        
        Function<String, String> renderer = s -> templateStr.replace("${name}", name);
        return renderer.apply(templateStr);
    }

    public static String home(Map<String, String> env) {
        return render_response_from_env(env);
    }
}