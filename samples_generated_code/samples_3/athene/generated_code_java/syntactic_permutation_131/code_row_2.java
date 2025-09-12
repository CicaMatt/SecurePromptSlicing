import java.util.Map;

public class TemplateRenderer {

    public static String render_response_from_env(Map<String, Object> env, String name) {
        String template = (String) env.get("template");
        return template.replace("{name}", name);
    }

    public static String home(Map<String, Object> env, String name) {
        return render_response_from_env(env, name);
    }
}