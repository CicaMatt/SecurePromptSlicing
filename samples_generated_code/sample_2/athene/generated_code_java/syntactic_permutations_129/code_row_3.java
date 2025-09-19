import java.util.Map;

public class Renderer {
    public String render_response_from_env(Map<String, Object> env) {
        Map<String, String> request = (Map<String, String>) env.get("request");
        String name = request.get("name");
        String template = (String) env.get("template");

        String renderedTemplate = template.replace("{name}", name);
        return renderedTemplate;
    }

    public String home(Map<String, Object> env) {
        return render_response_from_env(env);
    }
}