import java.util.Map;

public class Renderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.get("name");

        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}