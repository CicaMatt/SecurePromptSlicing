import java.util.Map;

public class App {
    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.getOrDefault("name", "World");

        String template = "<html><body><h1>Hello, {0}!</h1></body></html>";
        return template.replace("{0}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}