import java.util.Map;
import java.util.HashMap;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, Object> request = (Map<String, Object>) env.get("request");
        String name = (String) request.get("name");

        String template = (String) env.get("template");

        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}