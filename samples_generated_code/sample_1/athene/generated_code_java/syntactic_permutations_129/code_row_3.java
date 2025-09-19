import java.util.Map;

public class TemplateRenderer {
    public static String render_response_from_env(Map<String, Object> env) {
        Map<String, String[]> request = (Map<String, String[]>) env.get("request");
        String name = request.containsKey("name") ? request.get("name")[0] : "Guest";
        String template = (String) env.get("template");

        String renderedTemplate = template.replace("{name}", name);

        return renderedTemplate;
    }

    public static String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}